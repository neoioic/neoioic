"""Publish immutable tutorial snapshots to the repository's GitHub Wiki."""

import base64
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
from zoneinfo import ZoneInfo


PAGE = re.compile(r'NEOioic-Wiki-\((\d{8})(?:_(\d+))?\)\.md')


def wiki_token():
    token = os.environ.get('WIKI_TOKEN', '').strip()
    if token:
        return token
    server = os.environ.get('GITHUB_SERVER_URL', 'https://github.com')
    repository = os.environ.get('GITHUB_REPOSITORY', '')
    settings = f'{server}/{repository}/settings/secrets/actions'
    message = (
        'Wiki was not published: the WIKI_TOKEN Actions secret is missing or empty. '
        f'Add a repository secret named WIKI_TOKEN at {settings}, using a dedicated '
        'classic PAT with public_repo scope for a public repository (repo for a '
        'private repository). Enable Wiki and create its first page once, then '
        'rerun this workflow. GITHUB_TOKEN cannot replace this Wiki credential.'
    )
    print(f'::error title=Wiki configuration required::{message}', file=sys.stderr)
    summary = os.environ.get('GITHUB_STEP_SUMMARY')
    if summary:
        with open(summary, 'a', encoding='utf-8') as output:
            output.write(f'## Wiki was not published\n\n{message}\n')
    return None


def git(*args, cwd, env=None, check=True):
    return subprocess.run(['git', *args], cwd=cwd, env=env, check=check,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def publish(source, wiki, date, before=None):
    pages = []
    for path in wiki.glob('*.md'):
        match = PAGE.fullmatch(path.name)
        if match:
            pages.append((match[1], int(match[2] or 1), path))
    latest = max(pages, default=None, key=lambda item: item[:2])
    if latest and latest[2].read_bytes() == source:
        print('Wiki already contains this tutorial; nothing to publish.')
        return None
    if before == source and latest:
        print('Push did not change the tutorial; recovering unpublished content.')
    number = max((number for day, number, _ in pages if day == date), default=0) + 1
    suffix = date if number == 1 else f'{date}_{number}'
    title = f'NEOioic Wiki ({suffix})'
    path = wiki / f'NEOioic-Wiki-({suffix}).md'
    path.write_bytes(source)
    git('add', '--', path.name, cwd=wiki)
    git('commit', '-m', title, cwd=wiki)
    return title


def main():
    token = wiki_token()
    if token is None:
        return 1
    root = Path(__file__).resolve().parents[2]
    source = (root / 'docs/wiki.md').read_bytes()
    event = json.loads(Path(os.environ['GITHUB_EVENT_PATH']).read_text())
    # repository.pushed_at records the push, unlike the author's commit date.
    pushed = event.get('repository', {}).get('pushed_at')
    if os.environ['GITHUB_EVENT_NAME'] != 'push':
        pushed = None
    if isinstance(pushed, (int, float)):
        instant = datetime.fromtimestamp(pushed, timezone.utc)
    elif pushed:
        instant = datetime.fromisoformat(pushed.replace('Z', '+00:00'))
    else:
        instant = datetime.now(timezone.utc)
    date = instant.astimezone(ZoneInfo('Asia/Shanghai')).strftime('%Y%m%d')
    before = None
    revision = event.get('before', '')
    if revision and revision != '0' * 40:
        previous = git('show', f'{revision}:docs/wiki.md', cwd=root, check=False)
        if previous.returncode == 0:
            before = previous.stdout

    # Keep the token out of command arguments, URLs, logs and Git configuration.
    authorization = base64.b64encode(f'x-access-token:{token}'.encode()).decode()
    env = dict(os.environ, GIT_TERMINAL_PROMPT='0', GIT_CONFIG_COUNT='1',
               GIT_CONFIG_KEY_0='http.extraHeader',
               GIT_CONFIG_VALUE_0=f'AUTHORIZATION: basic {authorization}')
    url = f'{os.environ["GITHUB_SERVER_URL"]}/{os.environ["GITHUB_REPOSITORY"]}.wiki.git'
    with tempfile.TemporaryDirectory(prefix='neoioic-wiki-') as temporary:
        wiki = Path(temporary) / 'wiki'
        clone = git('clone', url, str(wiki), cwd=root, env=env, check=False)
        if clone.returncode:
            raise RuntimeError('Cannot access the Wiki. Enable Wiki in repository '
                               'settings, create its first page once in the GitHub '
                               'Wiki UI, and check WIKI_TOKEN permissions. Then rerun '
                               'this workflow; docs/wiki.md needs no artificial edit.')
        git('config', 'user.name', 'github-actions[bot]', cwd=wiki)
        git('config', 'user.email', '41898282+github-actions[bot]@users.noreply.github.com',
            cwd=wiki)
        title = publish(source, wiki, date, before)
        if title:
            git('push', 'origin', 'HEAD', cwd=wiki, env=env)
            print(f'Published {title}')
    return 0


if __name__ == '__main__':
    sys.exit(main())

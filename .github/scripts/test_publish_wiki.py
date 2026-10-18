"""Local Git integration checks; never contact or publish to GitHub."""

import importlib.util
import io
import os
from contextlib import redirect_stderr
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch


spec = importlib.util.spec_from_file_location(
    'publish_wiki', Path(__file__).with_name('publish_wiki.py'))
publisher = importlib.util.module_from_spec(spec)
spec.loader.exec_module(publisher)


class WikiPublicationTests(unittest.TestCase):
    def test_missing_token(self):
        with tempfile.TemporaryDirectory() as temporary:
            summary = Path(temporary) / 'summary.md'
            environment = {
                'WIKI_TOKEN': ' ',
                'GITHUB_REPOSITORY': 'neoioic/neoioic',
                'GITHUB_STEP_SUMMARY': str(summary),
            }
            with patch.dict(os.environ, environment, clear=True), \
                    redirect_stderr(io.StringIO()) as errors, \
                    patch.object(publisher, 'git') as git:
                self.assertEqual(publisher.main(), 1)
                git.assert_not_called()
            self.assertIn('::error title=Wiki configuration required::', errors.getvalue())
            self.assertIn('neoioic/neoioic/settings/secrets/actions', summary.read_text())
            self.assertIn('Wiki was not published', summary.read_text())

    def test_configured_token(self):
        with patch.dict(os.environ, {'WIKI_TOKEN': 'test-only-credential'}):
            self.assertEqual(publisher.wiki_token(), 'test-only-credential')

    def test_publication_history(self):
        with tempfile.TemporaryDirectory() as temporary:
            wiki = Path(temporary)
            for arguments in [('init',), ('config', 'user.name', 'Test'),
                              ('config', 'user.email', 'test@example.invalid')]:
                publisher.git(*arguments, cwd=wiki)
            source = '# Tutorial\n\n中文教程\n'.encode()
            # First deployment works even when this push did not edit the file.
            self.assertEqual(publisher.publish(source, wiki, '20261018', source),
                             'NEOioic Wiki (20261018)')
            self.assertIsNone(publisher.publish(source, wiki, '20261018', source))
            self.assertIsNone(publisher.publish(source, wiki, '20261019', source))
            changed = source + b'new content\n'
            self.assertEqual(publisher.publish(changed, wiki, '20261018', source),
                             'NEOioic Wiki (20261018_2)')
            # A revert is also a new version, not a duplicate of the oldest page.
            self.assertEqual(publisher.publish(source, wiki, '20261018', changed),
                             'NEOioic Wiki (20261018_3)')
            self.assertEqual(publisher.publish(changed, wiki, '20261019', changed),
                             'NEOioic Wiki (20261019)')
            self.assertEqual((wiki / 'NEOioic-Wiki-(20261018).md').read_bytes(), source)
            self.assertEqual(publisher.git('rev-list', '--count', 'HEAD', cwd=wiki)
                             .stdout.strip(), b'4')
            self.assertEqual(publisher.git('status', '--porcelain', cwd=wiki).stdout, b'')


if __name__ == '__main__':
    unittest.main()

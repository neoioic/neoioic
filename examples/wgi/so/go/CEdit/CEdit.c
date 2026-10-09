/**
 *
 * 文 件 名：CEdit.c
 *
 * 描    述：
 *
 * 创 建 者：
 *
 * 创建日期：
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>                <修改者>
 *   <修改内容...>
 *
 **/

#include "CEdit.h"
#include "../CObject/CObject.h"



void  TOG_CEdit(OBJECT* pObj);
RESULT  CEdit_I_Open(OBJECT* This, const VR* pCaller);
RESULT  CEdit_I_Close(OBJECT* This, const VR* pCaller);
RESULT  CEdit__CMD_PREPARE(OBJECT* This, const VR* pCaller);
RESULT  CEdit__CMD_INITIALIZE(OBJECT* This, const INIT_CEDIT* piced, const VR* pCaller);
RESULT  CEdit__CMD_WGI_INSERTCHARATCP(OBJECT* This, const TCHAR* archar, long count, const VR* pCaller);
RESULT  CEdit__MSG_WGI_ACTIVATE(OBJECT* This, const VR* pCaller);
RESULT  CEdit__MSG_WGI_DEACTIVATE(OBJECT* This, const VR* pCaller);
RESULT  CEdit__MSG_WGI_FOCUSDOWN(OBJECT* This, const POINT pt, const VR* pCaller);
RESULT  CEdit__CMD_WGI_MOVE(OBJECT* This, const MOVE* pmove, const VR* pCaller);


static long  SearchLLCharByChar (OBJECT* This, long iChar);
static long  SearchLFCharByChar (OBJECT* This, long iChar);
static void  CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(OBJECT* This, int maxLength);
static void  OVERCB_RDCScrollBar(OBJECT* This, const VR* pCaller);
static long  SearchCharByPoint (OBJECT* This, long x, long y);
static long  SearchTextLineByYCoord(OBJECT* This, long y);




/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> CObject </ibn>*/
/*<crt>*/
RESULT  CRT_CEdit(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  void  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  void  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  void  TOG_CObject(OBJECT* pObj);
	extern  void  TOG_VObject(OBJECT* pObj);
	extern  void  TOG_OIOIC(OBJECT* pObj);


	size_t   ux_ND = 4; 	/* ND数量。*/
	size_t   ux_BN = 6; 	/* 各ND的BN数量之和。*/
	size_t   ux_IB = 3; 	/* 各ND的IBN数量之和。*/
	size_t   ux_CS = NumCR * 10; 	/* 各ND的最少CS数量之和。*/
	size_t   ux_EM = OIOIC_ALIGNED_SIZE(EM_CEDIT) + OIOIC_ALIGNED_SIZE(EM_COBJECT) + OIOIC_ALIGNED_SIZE(EM_VOBJECT)
		 + OIOIC_ALIGNED_SIZE(EM_OIOIC); 	/* 各ND的EM尺寸之和。*/

	size_t  sum = ux_ND * sizeof(OBJECT) 	/* for AND. */
		 + ux_BN * sizeof(OBJECT*) 	/* for "ppo_ABN". */
		 + ux_IB * sizeof(OBJECT*) 	/* for "ppo_AIB". */
		 + ux_CS * sizeof(VR) + ux_EM; 	/* for "pvr_ACS" and "pEM". */


	BYTE*  pIC = NULL;

	if(NULL == pExotic)
	{
		*ppObj = NULL;
		pIC = (BYTE*)calloc(sum, 1);
	}else
	{
		pIC = pExotic;
	}


	if( pIC != NULL )
	{
		OBJECT*  pND;
		MLDSN    ArrMsn[3];
		BYTE*    p = pIC + sizeof(OBJECT) * ux_ND;


		/***  确定AND各元素  ***/

		/** CEdit **/
		pND = (OBJECT*)pIC;
		TOG_CEdit(pND);
		pND->MSN = MSN_CEDIT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** CObject **/
		TOG_CObject(++pND);
		pND->MSN = MSN_COBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** VObject **/
		TOG_VObject(++pND);
		pND->MSN = MSN_VOBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** OIOIC **/
		TOG_OIOIC(++pND);
		pND->MSN = MSN_OIOIC;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;


		/***  初始化各ND  ***/

		/** CEdit **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		ArrMsn[1] = MSN_VOBJECT;
		ArrMsn[2] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 3);
		p += sizeof(OBJECT*) * 3;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_CEDIT);

		/** CObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		ArrMsn[1] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 2);
		p += sizeof(OBJECT*) * 2;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_COBJECT);

		/** VObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 3;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += OIOIC_ALIGNED_SIZE(EM_VOBJECT);

		/** OIOIC **/
		++pND;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 4;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		if( IQCty > 0 )
		{
			/* - IQ - */
			((EM_OIOIC*)(pND->pEM))->IQ.Dtrm = (BYTE*)calloc(IQCty, 1);
			if( NULL == ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm)
			{
				/* 分配IQ的容量失败！*/
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->IQ.Front = ((EM_OIOIC*)(pND->pEM))->IQ.Rear = ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->IQ.Cty = IQCty;
			((EM_OIOIC*)(pND->pEM))->IQ.Qty = ((EM_OIOIC*)(pND->pEM))->IQ.Lost = 0;
		}

		if( OQCty > 0 )
 		{
			/* - OQ - */
			((EM_OIOIC*)(pND->pEM))->OQ.Dtrm = (BYTE*)calloc(OQCty, 1);
			if(NULL == ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm)
			{
				/* 分配OQ的容量失败！*/
				if( ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm != NULL )
					free(((EM_OIOIC*)(pND->pEM))->IQ.Dtrm);
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->OQ.Front = ((EM_OIOIC*)(pND->pEM))->OQ.Rear = ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->OQ.Cty = OQCty;
			((EM_OIOIC*)(pND->pEM))->OQ.Qty = ((EM_OIOIC*)(pND->pEM))->OQ.Lost = 0;
		}
		p += OIOIC_ALIGNED_SIZE(EM_OIOIC);
	}else
	{
		return R_N;
	}


	if(NULL == pExotic)
		*ppObj = (OBJECT*)pIC;


	return R_P;
}
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：CEdit_Open
*/
static  RESULT  CEdit_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;


	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return CEdit_I_Open(This, &caller);
}

/**
*
* 名称：CEdit_Input
*/
static  RESULT  CEdit_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：CEdit_Output
*/
static  RESULT  CEdit_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：CEdit_IOput
*/
static  RESULT  CEdit_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：CEdit_Interact0
*/
static  RESULT  CEdit_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR   caller;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		return CEdit__CMD_PREPARE(This, &caller);
	case MSG_WGI_ACTIVATE:
		return CEdit__MSG_WGI_ACTIVATE(This, &caller);
	case MSG_WGI_DEACTIVATE:
		return CEdit__MSG_WGI_DEACTIVATE(This, &caller);
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：CEdit_Interact1
*/
static  RESULT  CEdit_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：CEdit_Interact2
*/
static  RESULT  CEdit_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_INITIALIZE:
		assert(sizeof(INIT_CEDIT) == Qty);
		return CEdit__CMD_INITIALIZE(This, (INIT_CEDIT*)IStrm, &caller);
	case CMD_WGI_INSERTCHARATCP:
		return CEdit__CMD_WGI_INSERTCHARATCP(This, (TCHAR*)IStrm, (long)(Qty/sizeof(TCHAR)), &caller);
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == Qty);
		return CEdit__MSG_WGI_FOCUSDOWN(This, *(POINT*)IStrm, &caller);
	case CMD_WGI_MOVE:
		assert(sizeof(MOVE) == Qty);
		return CEdit__CMD_WGI_MOVE(This, (MOVE*)IStrm, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：CEdit_Interact3
*/
static  RESULT  CEdit_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：CEdit_Close
*/
static  RESULT  CEdit_Close(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

	return CEdit_I_Close(This, &caller);
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_CEdit
*/
void  TOG_CEdit(OBJECT* pObj)
{
	pObj->Open = CEdit_Open;
	pObj->Input = CEdit_Input;
	pObj->Output = CEdit_Output;
	pObj->IOput = CEdit_IOput;
	pObj->Interact0 = CEdit_Interact0;
	pObj->Interact1 = CEdit_Interact1;
	pObj->Interact2 = CEdit_Interact2;
	pObj->Interact3 = CEdit_Interact3;
	pObj->Close = CEdit_Close;
}


/*====================+ Function(s) +====================*/

/**
*
* NAME: CBF_OnMakeCurrentBitmap
* DESC: 在当前位图上定制内容，绘制文本，由VObject节点回调。
*/
static void CBF_OnMakeCurrentBitmap(OBJECT* This, const HDC  hDC)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	HFONT          hOldFont = NULL;
	COLORREF       crOldColor;
	HBITMAP        hOrigBmp, hNewBmp; 
	HDC            memdc;
	long           x, y;
	long           i, i1, i2;
	int            n;


	if(0 == pem->ti.clen)
		return;
	
	memdc = CreateCompatibleDC(hDC);	
	hNewBmp = CreateCompatibleBitmap(hDC, pem->vpw, pem->vph);
	hOrigBmp = GetCurrentObject(memdc, OBJ_BITMAP);
	SelectObject(memdc, hNewBmp);
	BitBlt(memdc, 0, 0, pem->vpw, pem->vph, hDC, pem_vob->rsc.rcinner.left, pem_vob->rsc.rcinner.top, SRCCOPY);

	n = pem->ti.nSpcRow / 2 + 1;
	x = -pem_vob->ox_irr;
	y = (pem->pArrCWXY[0].y > -pem_vob->oy_irr) ? pem->pArrCWXY[0].y : -pem_vob->oy_irr;	

	if(pem->ti.font)
		hOldFont = SelectObject(memdc, pem->ti.font);
	crOldColor = SetTextColor(memdc, pem->ti.crnor);

	while( y + pem_vob->oy_irr < pem->vph )
	{
		i1 = SearchCharByPoint(This, x, y);
		i2 = SearchCharByPoint(This, x+pem->vpw, y);
		if(-1 == i1 && i2 != -1)
		{
			i1 = SearchLFCharByChar(This, i2);
		}else if(i1 != -1 && -1 == i2)
		{
			i2 = SearchLLCharByChar(This, i1);
		}else if(-1 == i1 && -1 == i2)
		{
			i = SearchTextLineByYCoord(This, y);
			if(i < 0)
				break;
			if(pem->format & ETF_HCENTER) /* 水平居中？*/
			{
				i1 = SearchLFCharByChar(This, i);
				i2 = SearchLLCharByChar(This, i);
			}else
			{
				y = pem->pArrCWXY[i].y + pem->CharHeight + n;
				continue;
			}
		}
		
		for(i = i1; i<= i2; i++)
		{
			if(0x0A == pem->ti.text[i])
				continue; /* 换行符不需要显示。*/
		    //_Debug_OutputString(TEXT("\n TextOut  "), pem->ti.text[i], NULL);
			TextOut(memdc, pem->pArrCWXY[i].x + pem_vob->ox_irr, pem->pArrCWXY[i].y + pem_vob->oy_irr, pem->ti.text+i, 1);
		}

		if(i2 == pem->ti.clen-1)
			break;

		y = pem->pArrCWXY[i1].y + pem->CharHeight + n;
	}

	BitBlt(hDC, pem_vob->rsc.rcinner.left, pem_vob->rsc.rcinner.top, pem->vpw, pem->vph, memdc, 0, 0, SRCCOPY);

	if(hOldFont != NULL)
		SelectObject(memdc, hOldFont);
	SetTextColor(memdc, crOldColor);
	
	SelectObject(memdc, hOrigBmp);
	DeleteDC(memdc);
	
	if(hNewBmp != NULL)
		DeleteObject(hNewBmp);

	return;
}


/**
*
* NAME: CalcuTextSize
* DESC: 计算文本尺寸（宽度和高度）。
* RETU: 根据文本高度和宽度的变化情况，返回不同的数值。
*       0 - 宽度和高度都没变化；
*       1 - 只有宽度变化了，高度没变化；
*       2 - 只有高度变化了，宽度没变化；
*       3 - 宽度和高度都变化了。
*/
static int  CalcuTextSize(OBJECT* This)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           n, w, h, i, j, iLast;

	if(0 == pem->ti.clen)
	{
		w = 0;
		h = pem->CharHeight;
	}else
	{
		w = 0;
		i = 0;
		iLast = pem->ti.clen-1;
		
		while(1)
		{
			j = SearchLLCharByChar(This, i);
			n = pem->pArrCWXY[j].x + pem->pArrCWXY[j].w - pem->pArrCWXY[i].x;
			if(n > w)
				w = n;
			
			i = j+1;
			if(i >= iLast)
				break;
		}
		
		h = pem->pArrCWXY[iLast].y + pem->CharHeight - pem->pArrCWXY[0].y;
	}

    if(w != pem->textWidth && h != pem->textHeight)
	{
		pem->textWidth = w;
		pem->textHeight = h;
		return 3;
	}
	else if(h != pem->textHeight)
	{
		pem->textHeight = h;
		return 2;
	}else if(w != pem->textWidth)
	{
		pem->textWidth = w;
		return 1;
	}
		
	return 0;
}

/**
*
* NAME: CalcuSceneSize
* DESC: 计算情景尺寸（宽度和高度）。
*/
static void  CalcuSceneSize(OBJECT* This)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	int            n;
	
	n = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	pem_vob->scenew = pem->textWidth > n ? pem->textWidth : n;
	n = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;
	pem_vob->sceneh = pem->textHeight > n ? pem->textHeight : n;

	return;
}

/**
*
* NAME: CalcuViewportSize
* DESC: 计算视口尺寸（宽度和高度）。
*/
static void  CalcuViewportSize(OBJECT* This)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	int            w, h;

	w = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	h = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;

	if(pem->style & EDTS_SCROLLBAR)
	{
		pem->vpw = w;
		pem->vph = h;
		return;
	}

	if(pem_vob->scenew > w)
	{
		pem->vph = h - pem->i2hscb.nThickness;
		pem->vpw = (pem_vob->sceneh > h - pem->i2hscb.nThickness) ? w - pem->i2vscb.nThickness : w;
	}else
	{
		if(pem_vob->sceneh > h)
		{
			pem->vpw = w - pem->i2vscb.nThickness;
			pem->vph = (pem_vob->scenew > w - pem->i2vscb.nThickness) ? h - pem->i2hscb.nThickness : h;
		}else
		{
			pem->vpw = w;
			pem->vph = h;
		}
	}

	return;
}


/**
*
* NAME: FormatText
* DESC: 格式化指定文本段的每一行。
*/
static void  FormatText(OBJECT* This, long iBegin, long iEnd)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	long           i, j, k, n;
	int            dx, dy;

	assert(iBegin < iEnd);

	
	if(pem->format & ETF_TOP)
	{
		dy = -pem->pArrCWXY[0].y;
	}else if(pem->format & ETF_BOTTOM)
	{
		dy = pem_vob->sceneh - pem->textHeight - pem->pArrCWXY[0].y;
	}else  // ETF_VCENTER
	{
		dy = (pem_vob->sceneh - pem->textHeight) / 2 - pem->pArrCWXY[0].y;
	}
	
	i = iBegin;

	do{
		j = SearchLFCharByChar (This, i);
		k = SearchLLCharByChar (This, i);
		if(pem->format & ETF_LEFT)
		{
			dx = -pem->pArrCWXY[j].x;
		}else if(pem->format & ETF_RIGHT)
		{
			dx = pem_vob->scenew - pem->pArrCWXY[k].x - pem->pArrCWXY[k].w;
		}else // ETF_HCENTER
		{
			n = pem->pArrCWXY[k].x + pem->pArrCWXY[k].w - pem->pArrCWXY[j].x;
			dx = (pem_vob->scenew - n) / 2 - pem->pArrCWXY[j].x;
		}

		for(i = j; i<=k; i++)
		{
			pem->pArrCWXY[i].x += dx;
			pem->pArrCWXY[i].y += dy;
		}
		 
		i = k+1;
	}while(i < iEnd);

	return;
}


/**
*
* NAME: SetCaretPosition
* DESC: 根据参数iChar和bToRight设置插入符位置。
* RETU: 0 - 没重画；1 - 重画了。
*/
static int  SetCaretPosition(OBJECT* This, long iChar, OIOIC_BOOL bToRight, const VR* pCaller)
{
	EM_CEDIT*     pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*   pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	long          x, y, dx, dy;
	int           rv, n1, n2, m1, m2;

	if(-1 == iChar)
	{
		n1 = pem->vpw - pem->CaretWidth;
		n2 = n1 / 2;
		m1 = pem->vph - pem->CharHeight;
		m2 = m1 / 2;
		
		x = pem_vob->rsc.rcinner.left;
		y = pem_vob->rsc.rcinner.top;
		
		if(pem->format & ETF_RIGHT)
			x += n1;
		else if(pem->format & ETF_HCENTER)
			x += n2;
		
		if(pem->format & ETF_BOTTOM )
			y += m1;
		else if(pem->format & ETF_VCENTER)
			y += m2;

		rv = 0;
	}else
	{	
		dx = pem ->pArrCWXY[iChar].x + pem_vob->ox_irr;
		if(TRUE == bToRight)
			dx += pem ->pArrCWXY[iChar].w;
		dy = pem ->pArrCWXY[iChar].y + pem_vob->oy_irr;
	
		if(dx > 0)
		{
			dx += pem->CaretWidth - pem->vpw;
			if(dx < 0)
				dx = 0;
		}

		if(dy > 0)
		{
			dy += pem->CharHeight - pem->vph;
			if(dy < 0)
				dy = 0;
		}

		if(dx != 0 || dy != 0 ) /* 插入符在新位置不能完全出现在视口内？*/
		{
			pem_vob->ox_irr -= dx;
			pem_vob->oy_irr -= dy;

			// ........ 在这里用CMD_WGI_ROLLONCB行为访问滚动条。

			VO_Interact0(pem->pVObject, CMD_WGI_REPAINT, pCaller);
			rv = 1;
		}

		rv = 0;

		x = pem ->pArrCWXY[iChar].x + pem_vob->ox_irr + pem_vob->rsc.rcinner.left;
		if(TRUE == bToRight)
			x += pem ->pArrCWXY[iChar].w;
		y = pem ->pArrCWXY[iChar].y + pem_vob->oy_irr + pem_vob->rsc.rcinner.top;
	}


	do{ /* 把坐标转换到窗口对象的外部矩形坐标。*/	
		x += pem_vob->rsc.rcouter.left;
		y += pem_vob->rsc.rcouter.top;
		pem_vob = (EM_VOBJECT*)GetEMofBN(pem_vob->pSuperior, MSN_VOBJECT);
		x += pem_vob->rsc.rcinner.left;
		y += pem_vob->rsc.rcinner.top;
	}while(pem_vob->pSuperior != NULL);

	SetCaretPos(x, y);
	ShowCaret(*pem_vob->pWndHandle);

	pem->cp.iChar = iChar;
	pem->cp.bToRight = bToRight;


	return rv; 
}


/**
*
* NAME: SearchTextLineByYCoord
* DESC: 给定情景区域内一个纵坐标值，确定该值属于哪个文本行的行定位区域的纵坐标区间。
*/
static long  SearchTextLineByYCoord(OBJECT* This, long y)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           i, n1, n2, left, middle, right;
	int            m1, m2;
	
	left = 0;
	right = pem->ti.clen - 1;
	i = -1;
	m1 = pem->ti.nSpcRow / 2;
	m2 = pem->CharHeight + m1;

	while(left <= right)
	{
		middle = (left+right) / 2;
		n1 = pem->pArrCWXY[middle].y - m1;
		n2 = pem->pArrCWXY[middle].y + m2;
		
		if (y >= n1 && y <= n2) 
		{
			i = middle;
			break;
		}else if (y < n1) 
			right = middle-1;
		else 
			left = middle + 1;
	}
	
	return i;
}

/**
*
* NAME: SearchCharByPoint
* DESC: 给定最大滚动区域内一个点的坐标，确定该点左哪个字符的定位区域。
*/
static long  SearchCharByPoint (OBJECT* This, long x, long y)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           i, n1, n2, left, middle, right;
	int            m;
	
	
	// 先确定属于哪一行：
	i = SearchTextLineByYCoord(This, y);
	if(-1 == i)
		return -1;
	
	// 确定属于哪一个字符：
	m = pem->ti.nSpcClm / 2;
	n1 = pem->pArrCWXY[i].x - m;
	n2 = pem->pArrCWXY[i].x + pem->pArrCWXY[i].w + m;

	if(x >= n1 && x <= n2)
	{
		return i;
	}else
	{
		left = SearchLFCharByChar (This, i);
		right = SearchLLCharByChar (This, i);
	}
	
	while(left <= right)
	{
		middle = (left+right) / 2;
		n1 = pem->pArrCWXY[middle].x - m;
		n2 = pem->pArrCWXY[middle].x + pem->pArrCWXY[middle].w + m;
		if(x >= n1 && x <= n2)
			return  middle;
		else if(x < n1) 
			right = middle-1;
		else 
			left = middle + 1;
	}
	
	return  -1;
}

/**
*
* NAME: SearchLFCharByChar
* DESC: 给定一个字符的索引，确定该字符所在文本行的第一个字符的索引。
*/
static long  SearchLFCharByChar(OBJECT* This, long iChar)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           y, left, middle = iChar, right;
	assert(iChar >= 0 && iChar < pem->ti.clen);
	

	left = 0;
	right = iChar;
	y = pem->pArrCWXY[iChar].y;
	
	while(left <= right)
	{
		middle = (left+right) / 2;
		if(pem->pArrCWXY[middle].y == y) 
		{
			right = middle-1;
			if(right == -1)
				break;
			else if(pem->pArrCWXY[right].y < y)
				break;	
		}else 
		{
			left = middle + 1;
		}
	}
	
	return  middle;
}

/**
*
* NAME: SearchLLCharByChar
* DESC: 给定一个字符的索引，确定该字符所在文本行的最后一个字符的索引。
*/
static long  SearchLLCharByChar (OBJECT* This, long iChar)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           n, y, left, middle = iChar, right;
	assert(iChar >= 0 && iChar < pem->ti.clen);
	

	n = pem->ti.clen;
	y = pem->pArrCWXY[iChar].y;
	right = n - 1;
	left = iChar;
	
	while(left <= right)
	{
		middle = (left+right) / 2;
		if(pem->pArrCWXY[middle].y == y) 
		{
			left = middle + 1;
			if(left == n)
				break;
			else if(pem->pArrCWXY[left].y > y)
				break;	
		}else 
		{
			right = middle-1;
		}
	}
	
	return  middle;
}


/**
*
* NAME: OVERCB_InsertInitialText
* DESC: 在当前位图上方（不是上面）插入初始化的文本，计算字符宽度和
*       坐标以及判断是否需要创建滚动条。只在CMD_PREPARE行为中调用。
*/
static void  OVERCB_InsertInitialText(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	HDC            hdc;
	SIZE           size;
	long           i, n, x, y; 
	int            vpw, vph; 


	if(0 == pem->ti.clen)
		return;

	n = pem->ti.clen;

	/* 计算每个新字符的宽度 */

	hdc = GetDC(*pem_vob->pWndHandle);
	for(i = 0; i < n; i++)
	{
		if(0x0A == pem->ti.text[i])
		{
			/* 换行符也有宽度，但不需显示换行符，所以记录换行符的宽度为0。*/
			pem->pArrCWXY[i].w = 0;
		}else
		{
			GetTextExtentPoint32(hdc, pem->ti.text+i, 1, &size);
			pem->pArrCWXY[i].w = size.cx;
		}
	}
	ReleaseDC(*pem_vob->pWndHandle, hdc);


	/* 计算字符的位置 */

	vpw = pem->vpw;
	vph = pem->vph;
	x = y = 0;

	if(pem->style & EDTS_AUTOWRAP) /* 自动换行？*/
	{
		if((pem->pVScrBar != NULL) || !(pem->style & EDTS_SCROLLBAR)) /* 有纵向滚动条，或者，控件没有滚动条风格？*/
		{
			for(i = 0; i < n; i++)
			{
				if(0x0A == pem->ti.text[i]) /* 是换行符？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}else if(x + pem->pArrCWXY[i].w > vpw) /* 超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}
		}else /* 没有纵向滚动条，并且，控件有滚动条风格。*/
		{
			for(i = 0; i < n; i++)
			{
				if(0x0A == pem->ti.text[i]) /* 是换行符？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
					{
						CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
						break;
					}else
					{
						pem->pArrCWXY[i].x = 0;
						pem->pArrCWXY[i].y = y;
						x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
					}
				}else if(x + pem->pArrCWXY[i].w > vpw) /* 超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
					{
						CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
						break;
					}else
					{
						pem->pArrCWXY[i].x = 0;
						pem->pArrCWXY[i].y = y;
						x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
					}
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}
		}
	}else /* 不是自动换行。*/
	{
		for(i = 0; i < n; i++)
		{
			if(0x0A == pem->ti.text[i]) /* 是换行符？*/
			{
				y += pem->CharHeight + pem->ti.nSpcRow;
				pem->pArrCWXY[i].x = 0;
				pem->pArrCWXY[i].y = y;
				x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
			}else
			{
				pem->pArrCWXY[i].x = x;
				pem->pArrCWXY[i].y = y;
				x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
			}
		}
	}

	CalcuTextSize(This);
	CalcuSceneSize(This);
	CalcuViewportSize(This);

	if( !((pem->format & ETF_LEFT) && (pem->format & ETF_TOP)) )
		FormatText(This, 0, pem->ti.clen-1);

	OVERCB_RDCScrollBar(This, pCaller);

	return;
}


/**
*
* NAME: InsertCharacter
* DESC: 在插入符位置插入一个或多个字符。
*/
static void  InsertCharacter(OBJECT* This, long iat, const TCHAR* archar, long count, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	HDC            hdc;
	SIZE           size;
	long           i, j, n, x, y; 
	long           iNCB, iNCE, nNCN;  /* NCB: New Character Begin, NCE: New Character End, NCN : New Character Number */
	int            vpw, vph, r; 

	n = pem->ti.cpty - pem->ti.clen;
	nNCN = count < n ? count : n; 

	if(0 == nNCN)
		return;

	iNCB = iat;

	if(pem->ti.clen > 0)
	{
		memmove(pem->ti.text + iNCB + nNCN, pem->ti.text + iNCB, (pem->ti.clen - iNCB) * sizeof(TCHAR));
		memmove(pem->pArrCWXY + iNCB + nNCN, pem->pArrCWXY + iNCB, (pem->ti.clen - iNCB) * sizeof(CWXY));
	}
	memcpy(pem->ti.text+iNCB, archar, nNCN * sizeof(TCHAR));
	pem->ti.clen += nNCN;

	iNCE = iNCB + nNCN - 1;


	/* 计算每个新字符的宽度 */

	hdc = GetDC(*pem_vob->pWndHandle);
	for(i = 0; i < nNCN; i++)
	{
		if(0x0A == archar[i])
		{
			/* 换行符也有宽度，但不需显示换行符，所以记录换行符的宽度为0。*/
			pem->pArrCWXY[iNCB+i].w = 0;
		}else
		{
			GetTextExtentPoint32(hdc, archar+i, 1, &size);
			pem->pArrCWXY[iNCB+i].w = size.cx;
		}
	}
	ReleaseDC(*pem_vob->pWndHandle, hdc);


	/* 计算字符的位置 */

	vpw = pem->vpw;
	vph = pem->vph;

	if(0 == iNCB)
	{
		x = 0;
		y = 0;
	}else
	{
		x = pem->pArrCWXY[iNCB-1].x + pem->pArrCWXY[iNCB-1].w + pem->ti.nSpcClm;
		y = pem->pArrCWXY[iNCB-1].y;
	}

	i = iNCB;
	j = iNCB + nNCN;

	if(pem->style & EDTS_AUTOWRAP) /* 自动换行？*/
	{
		if((pem->pVScrBar != NULL) || !(pem->style & EDTS_SCROLLBAR)) /* 有纵向滚动条，或者，控件没有滚动条风格？*/
		{
			/* 先计算新字符的位置 */	

			for(; i < j; i++)
			{
				if(0x0A == pem->ti.text[i] || x + pem->pArrCWXY[i].w > vpw) /* 是换行符，或者，超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}

			/* 再计算后面字符的位置 */

			j = pem->ti.clen;

			for(; i < j; i++)
			{
				if(0x0A == pem->ti.text[i]) /* 是换行符？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(pem->pArrCWXY[i].y == y) /* 满足中途结束条件？*/
					{
						break;
					}else 
					{
						pem->pArrCWXY[i].x = 0;
						pem->pArrCWXY[i].y = y;
						x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
					}
				}else if(x + pem->pArrCWXY[i].w > vpw) /* 超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}
		}else /* 没有纵向滚动条，并且，控件有滚动条风格。*/
		{
			/* 先计算新字符的位置 */	
			
			for(; i < j; i++)
			{
				if(0x0A == pem->ti.text[i] || x + pem->pArrCWXY[i].w > vpw) /* 是换行符，或者，超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
					{
						CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
						goto INSERTCHAR_GT;
					}
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}
			
			/* 再计算后面字符的位置 */
			
			j = pem->ti.clen;
			
			for(; i < j; i++)
			{
				if(0x0A == pem->ti.text[i]) /* 是换行符？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(pem->pArrCWXY[i].y == y) /* 满足中途结束条件。*/
					{
						if(pem->pArrCWXY[pem->ti.clen-1].y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
						{
							CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
							goto INSERTCHAR_GT;
						}else
						{
							break;
						}
					}else 
					{
						if(y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
						{
							CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
							goto INSERTCHAR_GT;
						}else
						{
							pem->pArrCWXY[i].x = 0;
							pem->pArrCWXY[i].y = y;
							x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
						}
					}
				}else if(x + pem->pArrCWXY[i].w > vpw) /* 超过最大行长度？*/
				{
					y += pem->CharHeight + pem->ti.nSpcRow;
					if(y + pem->CharHeight - pem->pArrCWXY[0].y > vph) /* 需要加纵向滚动条？*/
					{
						CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(This, vpw - pem->i2vscb.nThickness);
						goto INSERTCHAR_GT;
					}else
					{
						pem->pArrCWXY[i].x = 0;
						pem->pArrCWXY[i].y = y;
						x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
					}
				}else
				{
					pem->pArrCWXY[i].x = x;
					pem->pArrCWXY[i].y = y;
					x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}
		}
	}else /* 不是自动换行。*/
	{
		/* 先计算新字符的位置 */	
		
		for(; i < j; i++)
		{
			if(0x0A == pem->ti.text[i]) /* 是换行符？*/
			{
				y += pem->CharHeight + pem->ti.nSpcRow;
				pem->pArrCWXY[i].x = 0;
				pem->pArrCWXY[i].y = y;
				x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
			}else
			{
				pem->pArrCWXY[i].x = x;
				pem->pArrCWXY[i].y = y;
				x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
			}
		}
		
		/* 再计算后面字符的位置 */
		
		j = pem->ti.clen;
		
		for(; i < j; i++)
		{
			if(0x0A == pem->ti.text[i]) /* 是换行符？*/
			{
				y += pem->CharHeight + pem->ti.nSpcRow;
				if(pem->pArrCWXY[i].y == y) /* 满足中途结束条件？*/
				{
					break;
				}else
				{
					pem->pArrCWXY[i].x = 0;
					pem->pArrCWXY[i].y = y;
					x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
				}
			}else
			{
				pem->pArrCWXY[i].x = x;
				pem->pArrCWXY[i].y = y;
				x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
			}
		}
	}

INSERTCHAR_GT:

	r = CalcuTextSize(This);
	CalcuSceneSize(This);
	CalcuViewportSize(This);

	if( !((pem->format & ETF_LEFT) && (pem->format & ETF_TOP)) )
	{
		if(0 == r)
			FormatText(This, iNCB, iNCE);
		else
			FormatText(This, 0, pem->ti.clen-1);
	}

	OVERCB_RDCScrollBar(This, pCaller);
	if(0 == SetCaretPosition(This, iNCE, TRUE, pCaller))
		VO_Interact0(pem->pVObject, CMD_WGI_REPAINT, pCaller);

	return;
}

/**
*
* NAME: InitHScrollBar
* DESC: 初始化横向滚动条。
*/
static void  InitHScrollBar(OBJECT* This, const VR* pCaller)
{
	return;
}

/**
*
* NAME: InitVScrollBar
* DESC: 初始化纵向滚动条。
*/
static void  InitVScrollBar(OBJECT* This, const VR* pCaller)
{
	return;
}


/**
*
* NAME: DestroyHScrollBar
* DESC: 销毁横向滚动条。
*/
static void  DestroyHScrollBar(OBJECT* This, const VR* pCaller)
{
	return;
}


/**
*
* NAME: DestroyVScrollBar
* DESC: 销毁纵向滚动条。
*/
static void  DestroyVScrollBar(OBJECT* This, const VR* pCaller)
{
	return;
}


/**
*
* NAME: OVERCB_RDCScrollBar
* DESC: 在当前位图的上方（不是上面）重置或销毁或创建滚动条。
*/
static void  OVERCB_RDCScrollBar(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	ROLLINGARG     rarg;
	int            w, h;


	w = pem_vob->rsc.rcinner.right - pem_vob->rsc.rcinner.left;
	h = pem_vob->rsc.rcinner.bottom - pem_vob->rsc.rcinner.top;

	if(!(pem->style & EDTS_SCROLLBAR))
	{
		if(pem->pHScrBar != NULL)
			DestroyHScrollBar(This, pCaller);
		if(pem->pVScrBar != NULL)
			DestroyVScrollBar(This, pCaller);
		return;
	}else
	{
		if(pem->vpw < w && pem->vph < h)
		{
			if(pem->pHScrBar != NULL && pem->pVScrBar != NULL)
			{
				VO_Interact2(pem->pHScrBar, CMD_WGI_ROLLONCB, (BYTE*)&rarg, sizeof(ROLLINGARG), pCaller);
				VO_Interact2(pem->pVScrBar, CMD_WGI_ROLLONCB, (BYTE*)&rarg, sizeof(ROLLINGARG), pCaller);
				return;
			}
		}else if(pem->vpw < w)
		{
			if(NULL == pem->pHScrBar && pem->pVScrBar != NULL)
			{
				VO_Interact2(pem->pVScrBar, CMD_WGI_ROLLONCB, (BYTE*)&rarg, sizeof(ROLLINGARG), pCaller);
				return;
			}
		}else if(pem->vph < h)
		{
			if(pem->pHScrBar != NULL && NULL == pem->pVScrBar)
			{
				VO_Interact2(pem->pHScrBar, CMD_WGI_ROLLONCB, (BYTE*)&rarg, sizeof(ROLLINGARG), pCaller);
				return;
			}
		}else //视口宽度和高度等于内部矩形宽度和高度。
		{
			if(pem->pHScrBar != NULL)
				DestroyHScrollBar(This, pCaller);
			if(pem->pVScrBar != NULL)
				DestroyVScrollBar(This, pCaller);	
			return;
		}
		
		if(pem->pHScrBar != NULL)
			DestroyHScrollBar(This, pCaller);
		if(pem->pVScrBar != NULL)
			DestroyVScrollBar(This, pCaller);
		
		if(pem->vpw < w)
		{
			CreateObject(MSN_CSCROLLBAR, 0, 0, 1, &pem->pHScrBar);
			InitHScrollBar(This, pCaller);
		}
		
		if(pem->vph < h)
		{
			CreateObject(MSN_CSCROLLBAR, 0, 0, 1, &pem->pVScrBar);
			InitVScrollBar(This, pCaller);
		}
	}
	
	return;
}

/**
*
* NAME: CalcuAllCharacterXY_LEFTTOP_AUTOWRAP
* DESC: 按左靠齐和顶靠齐格式化方式及自动换行风格，计算所有字符的位置。
* PARA: maxLength-行的最大长度。
*/
static void  CalcuAllCharacterXY_LEFTTOP_AUTOWRAP(OBJECT* This, int maxLength)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           i, j, x, y; 
	
	x = y = 0;
	j = pem->ti.clen;
	
	for(i = 0; i < j; i++)
	{
		if(0x0A == pem->ti.text[i] || x + pem->pArrCWXY[i].w > maxLength) /* 是换行符，或者，超过最大行长度？*/
		{
			y += pem->CharHeight + pem->ti.nSpcRow;
			pem->pArrCWXY[i].x = 0;
			pem->pArrCWXY[i].y = y;
			x = pem->pArrCWXY[i].w + pem->ti.nSpcClm;
		}else
		{
			pem->pArrCWXY[i].x = x;
			pem->pArrCWXY[i].y = y;
			x += pem->pArrCWXY[i].w + pem->ti.nSpcClm;
		}
	}

	return;
}

/*=======================================================*/


/**
*
* NAME: CEdit_I_Open
*/
RESULT  CEdit_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC);
		pem->pVObject = GetBN(This, MSN_VOBJECT);
		pem->pCObject = GetBN(This, MSN_COBJECT);

		return RP_RCONE;
	}
	
	return R_P;
}

/**
*
* NAME: CEdit_I_Close
*/
RESULT  CEdit_I_Close(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	
	if(0 == This->RefCnt)
	{
		if(pem->pArrCWXY)
			free(pem->pArrCWXY);
		return RP_RCZERO;
	}
	
	return R_P;
}


/**
*
* NAME: CEdit__CMD_INITIALIZE
*/
RESULT  CEdit__CMD_INITIALIZE(OBJECT* This, const INIT_CEDIT* piced, const VR* pCaller)
{
	EM_CEDIT*        pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*      pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;

     
	pem_vob->onmcb.pCustomer = This;
	pem_vob->onmcb.OnMakeCurrentBitmap = CBF_OnMakeCurrentBitmap;
	pem->hBmpIntAreaVHScrbar = piced->hBmpIntAreaVHScrbar;
	pem->i2hscb = piced->i2hscb;
	pem->i2vscb = piced->i2vscb;
	pem->ti = piced->ti;
	pem->style = piced->style;
	pem->format = piced->format;
	pem->CaretWidth = piced->CaretWidth;
	
	return R_P;
}

/**
*
* NAME: CEdit__CMD_PREPARE
*/
RESULT CEdit__CMD_PREPARE(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*        pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*      pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	HFONT            hOldFont = NULL;
	HDC              hdc;
	TEXTMETRIC       tm;


	if(!(0x00000007L & pem->format))
		pem->format |= ETF_LEFT;

	if(!(0x00000038L & pem->format))
		pem->format |= ETF_TOP;

	if(0 == pem->CaretWidth)
		pem->CaretWidth = 1;

	if(pem->ti.cpty > 0)
	{
		pem->pArrCWXY = (CWXY*)calloc(pem->ti.cpty, sizeof(CWXY));
		if(NULL == pem->pArrCWXY)
			return R_N; 
	}

	hdc = GetDC(*pem_vob->pWndHandle);
	if(pem->ti.font)
		hOldFont = SelectObject(hdc, pem->ti.font);
	GetTextMetrics(hdc, &tm); 
	if(hOldFont != NULL)
		SelectObject(hdc, hOldFont);
	ReleaseDC(*pem_vob->pWndHandle, hdc);
	
	pem->CharHeight = tm.tmHeight; 

	OVERCB_InsertInitialText(This, pCaller);
	VO_Interact0(pem->pVObject, CMD_PREPARE, pCaller);

	return R_P;
}

/**
*
* NAME: CEdit__MSG_WGI_ACTIVATE
*/
RESULT  CEdit__MSG_WGI_ACTIVATE(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*    pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_VOBJECT*    pem_wob_sup;
	OIOIC_BOOL           flag; 


	pem_wob_sup = (EM_VOBJECT*)GetEMofBN(pem_vob->pSuperior, MSN_VOBJECT);
	flag = (This->po_AND != pem_wob_sup->pActiveSbdt) ? TRUE : FALSE; /* 标记是否需要创建插入符。*/
	
	VO_Interact0(pem->pVObject, MSG_WGI_ACTIVATE, pCaller);
	
	if(TRUE == flag) /* 需要创建插入符？*/
	{
		CreateCaret(*pem_vob->pWndHandle, NULL, pem->CaretWidth, pem->CharHeight);
		//_Debug_OutputString(TEXT("\nCreateCaret"), 123, NULL);
	}

	return R_P;
}

/**
*
* NAME: CEdit__MSG_WGI_DEACTIVATE
*/
RESULT  CEdit__MSG_WGI_DEACTIVATE(OBJECT* This, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;

	DestroyCaret(); /* 销毁插入符。*/
	VO_Interact0(pem->pVObject, MSG_WGI_DEACTIVATE, pCaller);

	return R_P;
}

/**
*
* NAME: CEdit__CMD_WGI_INSERTCHARATCP
*/
RESULT  CEdit__CMD_WGI_INSERTCHARATCP(OBJECT* This, const TCHAR* archar, long count, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	long           i; 
	
	
	if(-1 == pem->cp.iChar)
		return R_N;
	
	if(0 == pem->ti.clen)
		i = 0;
	else
		i = (TRUE == pem->cp.bToRight) ? pem->cp.iChar + 1 : pem->cp.iChar;
	
	InsertCharacter(This, i, archar, count, pCaller);
	
	return R_P;
}


/**
*
* NAME: CEdit__MSG_WGI_FOCUSDOWN
*/
RESULT  CEdit__MSG_WGI_FOCUSDOWN(OBJECT* This, const POINT pt, const VR* pCaller)
{
	EM_CEDIT*     pem = (EM_CEDIT*)This->pEM;
	EM_VOBJECT*   pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	long          x, y, i, j;


	VO_Interact2(pem->pVObject, MSG_WGI_FOCUSDOWN, (BYTE*)&pt, sizeof(POINT), pCaller);

    x = pt.x - pem_vob->rsc.rcinner.left;
	y = pt.y - pem_vob->rsc.rcinner.top;
	if(!(x > 0 && x < pem->vpw && y > 0 && y < pem->vph))
		return R_P; /* 不在视口内就返回。*/
	
	if(0 == pem->ti.clen)
	{
		SetCaretPosition(This, -1, TRUE, pCaller);
		return R_P;
	}
	
	
	x -= pem_vob->ox_irr;
	y -= pem_vob->oy_irr;
	j = pem->ti.clen - 1;
	
	if(y > pem->pArrCWXY[0].y && y < pem->pArrCWXY[j].y + pem->CharHeight)
	{
		i = SearchCharByPoint(This, x, y);
		if(-1 == i)
		{
			i = SearchTextLineByYCoord(This, y);
			i = SearchLFCharByChar(This, i);
			if(x < pem->pArrCWXY[i].x) /* 在行首字符前面？*/
			{
				if(0x0A == pem->ti.text[i]) /* 是换行符？*/
					SetCaretPosition(This, i, TRUE, pCaller);
				else
					SetCaretPosition(This, i, FALSE, pCaller);
			}else
			{
				i = SearchLLCharByChar(This, i);
				SetCaretPosition(This, i, TRUE, pCaller);
			}
		}else if(x < pem->pArrCWXY[i].x + pem->pArrCWXY[i].w / 2) /* 在i所指字符的定位区域的左半部？*/
		{
			if(0x0A == pem->ti.text[i]) /* 是换行符？*/
				SetCaretPosition(This, i, TRUE, pCaller);
			else if(0 ==i)
				SetCaretPosition(This, i, FALSE, pCaller);
			else if(pem->pArrCWXY[i-1].y < pem->pArrCWXY[i].y) /* “i-1”所指的字符在上一行？*/
				SetCaretPosition(This, i, FALSE, pCaller);
			else
				SetCaretPosition(This, i-1, TRUE, pCaller);
		}else
		{
			SetCaretPosition(This, i, TRUE, pCaller);
		}
	}else if(y <= pem->pArrCWXY[0].y)
	{
		SetCaretPosition(This, 0, FALSE, pCaller);
	}else
	{
		SetCaretPosition(This, j, TRUE, pCaller);
	}

	
	return R_P;
}


/**
*
* NAME: CEdit__CMD_WGI_MOVE
*/
RESULT  CEdit__CMD_WGI_MOVE(OBJECT* This, const MOVE* pmove, const VR* pCaller)
{
	EM_CEDIT*      pem = (EM_CEDIT*)This->pEM;
	POINT          pt;
	
	VO_Interact2(pem->pCObject, CMD_WGI_MOVE, (BYTE*)pmove, sizeof(MOVE), pCaller);

	GetCaretPos(&pt);

	pt.x += pmove->dxUL;
	pt.y += pmove->dyUL;
	SetCaretPos(pt.x, pt.y);
	
	return R_P;
}

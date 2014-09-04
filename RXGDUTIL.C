/*----------------------------------------------------------------------

   Support Routines for RXgdUtil.DLL

        Written by Andy Wysocki, 9/95
        Copyright 1995, AB Software
        Permission granted to use this code in any fashion provided
        that this notice is retained and any alterations are
        labeled as such. It is requested, but not required, that
        you share extensions to this module with me so that we
        can incorporate them into new versions.

  ----------------------------------------------------------------------*/
#define  INCL_VIO
#define  INCL_DOS
#define  INCL_ERRORS
#define  INCL_REXXSAA
#define  _DLL
#include <os2.h>
#include <rexxsaa.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include "gd.h"
#include "gdfontg.h"
#include "gdfontl.h"
#include "gdfontmb.h"
#include "gdfonts.h"
#include "gdfontt.h"

#define BUILDRXSTRING(t, s) { \
  strcpy((t)->strptr,(s));\
  (t)->strlength = strlen((s)); \
  }

#define BUILDRXULONG(t, s) { \
  sprintf((t)->strptr, "%u", (s));\
  (t)->strlength = strlen((t)->strptr); \
  }

#define BUILDRXLONG(t, s) { \
  sprintf((t)->strptr, "%d", (s));\
  (t)->strlength = strlen((t)->strptr); \
  }

#define OK_CALL         0
#define BAD_CALL        40

#define MAX_DIGITS      10


static PSZ RxFuncTable[] =
  {
  "RxgdImageCreate",          "RxgdImageCreate",
  "RxgdImageCreateFromGIF",   "RxgdImageCreateFromGIF",
  "RxgdImageDestroy",         "RxgdImageDestroy",
  "RxgdImageGIF",             "RxgdImageGIF",
  "RxgdImageSetPixel",        "RxgdImageSetPixel",
  "RxgdImageLine",            "RxgdImageLine",
  "RxgdImagePolygon",         "RxgdImagePolygon",
  "RxgdImageFilledPolygon",   "RxgdImagePolygon",
  "RxgdImageRectangle",       "RxgdImageRectangle",
  "RxgdImageFilledRectangle", "RxgdImageRectangle",
  "RxgdImageArc",             "RxgdImageArc",
  "RxgdImageFillToBorder",    "RxgdImageFillToBorder",
  "RxgdImageFill",            "RxgdImageFill",
  "RxgdImageColorAllocate",   "RxgdImageColorAllocate",
  "RxgdImageColorClosest",    "RxgdImageColorAllocate",
  "RxgdImageColorExact",      "RxgdImageColorAllocate",
  "RxgdImageString",          "RxgdImageString",
  "RxgdImageStringUp",        "RxgdImageString",
  "RxgdImageSetBrush",        "RxgdImageSetBrush",
  "RxgdImageSetTile",         "RxgdImageSetBrush",
  "RxgdImageSetStyle",        "RxgdImageSetStyle",
  "RxgdImageGetStyledBrushed","RxgdImageGetStyledBrushed",
  "RxgdImageBlue",            "RxgdImageGetColor",
  "RxgdImageRed",             "RxgdImageGetColor",
  "RxgdImageGreen",           "RxgdImageGetColor",
  "RxgdImageGetPixel",        "RxgdImageGetPixel",
  "RxgdImageSX",              "RxgdImageSxy",
  "RxgdImageSY",              "RxgdImageSxy",
  "RxgdImageBoundsSafe",      "RxgdImageBoundsSafe",
  "RxgdImageColorsTotal",     "RxgdImageGetTTI",
  "RxgdImageGetInterlaced",   "RxgdImageGetTTI",
  "RxgdImageGetTransparent",  "RxgdImageGetTTI",
  "RxgdImageColorDeallocate", "RxgdImageColorDeallocate",
  "RxgdImageColorTransparent","RxgdImageColorSet",
  "RxgdImageInterlace",       "RxgdImageColorSet",
  "RxgdImageCopy",            "RxgdImageCopy",
  "RxgdImageCopyResized",     "RxgdImageCopyResized",
  "RxgdImageSetColor",        "RxgdImageSetColor",
  "RxgdUnloadFuncs",          "RxgdUnloadFuncs",
  "RxgdLoadFuncs",            "RxgdLoadFuncs",
  };

/*********************************************************************/
/*  Declare all exported functions as REXX functions.                */
/*********************************************************************/
RexxFunctionHandler RxgdLoadFuncs;
RexxFunctionHandler RxgdUnloadFuncs;
RexxFunctionHandler RxgdImageCreate;
RexxFunctionHandler RxgdImageCreateFromGIF;
RexxFunctionHandler RxgdImageDestroy;
RexxFunctionHandler RxgdImageGIF;

RexxFunctionHandler RxgdImageSetPixel;
RexxFunctionHandler RxgdImageLine;
RexxFunctionHandler RxgdImagePolygon;
RexxFunctionHandler RxgdImageRectangle;
RexxFunctionHandler RxgdImageArc;
RexxFunctionHandler RxgdImageFillToBorder;
RexxFunctionHandler RxgdImageFill;

RexxFunctionHandler RxgdImageColorAllocate;
RexxFunctionHandler RxgdImageString;
RexxFunctionHandler RxgdImageSetBrush;
RexxFunctionHandler RxgdImageSetStyle;
RexxFunctionHandler RxgdImageGetStyledBrushed;

RexxFunctionHandler RxgdImageGetColor;
RexxFunctionHandler RxgdImageGetPixel;
RexxFunctionHandler RxgdImageSxy;
RexxFunctionHandler RxgdImageGetBoundsSafe;
RexxFunctionHandler RxgdImageGetTTI;
RexxFunctionHandler RxgdImageColorDeallocate;
RexxFunctionHandler RxgdImageColorSet;
RexxFunctionHandler RxgdImageCopy;
RexxFunctionHandler RxgdImageCopyResized;

RexxFunctionHandler RxgdImageSetColor;

/*----------------------------------------------------------------------*/
/* Debug routine - No use in normal code                                */
/*----------------------------------------------------------------------*/
#if 0
MyLog(char *_Str)
{
FILE    *FP;

  FP = fopen("rxgdutil.dbg", "ab");

  if (!FP)
    return;

  fwrite(_Str, 1, strlen(_Str), FP);
  fwrite("\r\n", 1, 2, FP);

  fclose(FP);

}
#endif

/*----------------------------------------------------------------------*/
/* RXGDLOADFUNCS -                                                      */
/*----------------------------------------------------------------------*/
ULONG RxgdLoadFuncs(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{

int     entries;
int     index;

  _Retstr->strlength = 0;

  if (_Argc > 0)                        /* Bad call to function         */
    return(BAD_CALL);                   /* Let REXX bomb                */

  entries = sizeof(RxFuncTable) / sizeof(PSZ);

  for (index = 0; index < entries; index+=2)
    RexxRegisterFunctionDll(RxFuncTable[index],
                            "RXGDUTIL",
                            RxFuncTable[index+1]);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/* RXGDUNLOADFUNCS -                                                    */
/*----------------------------------------------------------------------*/
ULONG RxgdUnloadFuncs(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{

int     entries;
int     index;

  _Retstr->strlength = 0;

  if (_Argc > 0)
    return(BAD_CALL);

  entries = sizeof(RxFuncTable) / sizeof(PSZ);

  for (index = 0; index < entries; index+=2)
    RexxDeregisterFunction(RxFuncTable[index]);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageCreate(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr   im;
ULONG   row, col;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  row = atol(_Argv[0].strptr);
  col = atol(_Argv[1].strptr);

  im = gdImageCreate(row, col);

  BUILDRXULONG(_Retstr, (ULONG)im);


  return(OK_CALL);                      /* no error on call           */
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageCreateFromGIF(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
FILE            *FP;
gdImagePtr      im;
ULONG           rc;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 1)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  FP = fopen(_Argv[0].strptr, "rb");    /* Open the GIF file            */

  if (!FP)                              /* Return a bad RC to caller    */
    {
    BUILDRXULONG(_Retstr, 1);
    return(OK_CALL);
    }

  im = gdImageCreateFromGif(FP);        /* Create internal memory str   */

  fclose(FP);

  BUILDRXULONG(_Retstr, (ULONG)im);     /* Return handle to caller      */

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageDestroy(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 1)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);

  gdImageDestroy(im);                   /* free up memory               */

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageGIF(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
FILE            *FP;
gdImagePtr      im;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);

  FP = fopen(_Argv[1].strptr, "wb");

  if (!FP)
    {
    BUILDRXULONG(_Retstr, 1);
    return(OK_CALL);
    }

  gdImageGif(im, FP);

  fclose(FP);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageSetPixel(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     x, y, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 4)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  x     = atol(_Argv[1].strptr);
  y     = atol(_Argv[2].strptr);
  color = atol(_Argv[3].strptr);

  gdImageSetPixel(im, x, y, color);

return(OK_CALL);
}



/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageLine(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     x1, x2, y1, y2, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 6)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  x1    = atol(_Argv[1].strptr);
  y1    = atol(_Argv[2].strptr);
  x2    = atol(_Argv[3].strptr);
  y2    = atol(_Argv[4].strptr);
  color = atol(_Argv[5].strptr);

  gdImageLine(im, x1, y1, x2, y2, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageRectangle(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     x1, x2, y1, y2, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 6)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  x1    = atol(_Argv[1].strptr);
  y1    = atol(_Argv[2].strptr);
  x2    = atol(_Argv[3].strptr);
  y2    = atol(_Argv[4].strptr);
  color = atol(_Argv[5].strptr);

  if (_Name[9] == 'R')                  /* SO I cheat here, it easier        */
                                        /* than making a function for each   */
                                        /* RxgdImageRectangle                */
    gdImageRectangle(im, x1, y1, x2, y2, color);
  else                                  /* RxgdImageFilledRectangle          */
    gdImageFilledRectangle(im, x1, y1, x2, y2, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageArc(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     cx, cy, w, h, s, e, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 8)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  cx    = atol(_Argv[1].strptr);
  cy    = atol(_Argv[2].strptr);
  w     = atol(_Argv[3].strptr);
  h     = atol(_Argv[4].strptr);
  s     = atol(_Argv[5].strptr);
  e     = atol(_Argv[6].strptr);
  color = atol(_Argv[7].strptr);

  gdImageArc(im, cx, cy, w, h, s, e, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageFillToBorder(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     x, y, border, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 5)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  x     = atol(_Argv[1].strptr);
  y     = atol(_Argv[2].strptr);
  border= atol(_Argv[3].strptr);
  color = atol(_Argv[4].strptr);

  gdImageFillToBorder(im, x, y, border, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageFill(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     x, y, color;

  BUILDRXULONG(_Retstr, 0);             /* Not created                */
                                        /* check arguments            */
  if (_Argc != 4)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  x     = atol(_Argv[1].strptr);
  y     = atol(_Argv[2].strptr);
  color = atol(_Argv[3].strptr);

  gdImageFill(im, x, y, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageColorAllocate(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     r, g, b;
int     rc;

                                        /* check arguments            */
  if (_Argc != 4)                       /* wrong number?              */
    return (BAD_CALL);                  /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  r     = atol(_Argv[1].strptr);
  g     = atol(_Argv[2].strptr);
  b     = atol(_Argv[3].strptr);

  switch(_Name[14])
    {
    case 'A':                           /* RxgdImageColorAllocate       */
      rc = gdImageColorAllocate(im, r, g, b);
      break;

    case 'C':                           /* RxgdImageColorClosest        */
      rc = gdImageColorClosest(im, r, g, b);
      break;

    case 'E':                           /* RxgdImageColorExact          */
      rc = gdImageColorExact(im, r, g, b);
      break;

    default:
      return(BAD_CALL);
    }

  BUILDRXLONG(_Retstr, rc);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/* NOTE: GD.LIB does not have function like this,  I needed a way to    */
/*      Change a specific color index, so I provide this function       */
/*----------------------------------------------------------------------*/
ULONG RxgdImageSetColor(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     r, g, b, index;
int     rc;

                                        /* check arguments            */
  if (_Argc != 5)                       /* wrong number?              */
    return (BAD_CALL);                  /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  index = atol(_Argv[1].strptr);
  r     = atol(_Argv[2].strptr);
  g     = atol(_Argv[3].strptr);
  b     = atol(_Argv[4].strptr);

  if (index > gdImageColorsTotal(im))
    rc = -1;
  else
    {
    ((im)->red[(index)])   = r;
    ((im)->green[(index)]) = g;
    ((im)->blue[(index)])  = b;
    rc = 0;
    }

  BUILDRXLONG(_Retstr, rc);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageString(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
gdFontPtr       fnt;
int     x, y, color;
char    c;

                                        /* check arguments            */
  if (_Argc != 6)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  c     = _Argv[1].strptr[0];
  x     = atol(_Argv[2].strptr);
  y     = atol(_Argv[3].strptr);
  color = atol(_Argv[5].strptr);

  switch (c)
    {
    case 't':
    case 'T':
      fnt = gdFontTiny;
      break;
    case 's':
    case 'S':
      fnt = gdFontSmall;
      break;
    case 'm':
    case 'M':
      fnt = gdFontMediumBold;
      break;
    case 'l':
    case 'L':
      fnt = gdFontLarge;
      break;
    case 'g':
    case 'G':
      fnt = gdFontGiant;
      break;
    default:
      fnt = gdFontMediumBold;
    }

  if (_Name[15] == 0)                   /* Just String                  */
    gdImageString(im, fnt, x, y, _Argv[4].strptr, color);
  else                                  /* StringUp call                */
    gdImageStringUp(im, fnt, x, y, _Argv[4].strptr, color);

  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImagePolygon(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     p, pt, color;
int     *points;
int     index;
LONG    rc;
SHVBLOCK  shv;
char    vname[256];
char    vbuf[256];
                                        /* check arguments            */
  if (_Argc != 4)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im     = (gdImagePtr)atol(_Argv[0].strptr);

  p      = atol(_Argv[2].strptr);
  pt     = p * 2;
  points = (int *) malloc(sizeof(int) * pt);

  color   = atol(_Argv[3].strptr);

                                        /* Go get the STEM variable          */
  for (index = 0; index < pt; index++ )
    {
    shv.shvnext  = 0;

    sprintf(vname, "%s.%d", _Argv[1].strptr, index);
    MAKERXSTRING(shv.shvname, vname, strlen(vname));

    MAKERXSTRING(shv.shvvalue, vbuf, sizeof(vbuf));

    shv.shvnamelen = strlen(vname);
    shv.shvvaluelen= sizeof(vbuf);
    shv.shvcode = RXSHV_SYFET;
    shv.shvret   = 0;
    rc = RexxVariablePool(&shv);

    points[index] = atol(shv.shvvalue.strptr);
    }

  if (_Name[9] == 'P')
    gdImagePolygon(im, (gdPointPtr)points, p, color);
  else
    gdImageFilledPolygon(im, (gdPointPtr)points, p, color);

  free(points);

  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageSetBrush(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im, br;

                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  br    = (gdImagePtr)atol(_Argv[1].strptr);

  if (_Name[12] == 'B')                 /* Shared function, check name  */
    {
    gdImageSetBrush(im, br);
    BUILDRXULONG(_Retstr, gdBrushed);
    }
  else
    {
    gdImageSetTile(im, br);
    BUILDRXULONG(_Retstr, gdTiled);
    }

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageSetStyle(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
gdImagePtr      im;
int     s, sp;
int     *style;
int     index;
SHVBLOCK  shv;
char    vname[256];
char    vbuf[256];
                                        /* check arguments            */
  if (_Argc != 3)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im     = (gdImagePtr)atol(_Argv[0].strptr);

  sp     = atol(_Argv[2].strptr);
  style  = (int *) malloc(sizeof(int) * sp);

                                        /* Get the STEM Variable             */
  for (index = 0; index < sp; index++ )
    {
    shv.shvnext  = 0;

    sprintf(vname, "%s.%d", _Argv[1].strptr, index);
    MAKERXSTRING(shv.shvname, vname, strlen(vname));

    MAKERXSTRING(shv.shvvalue, vbuf, sizeof(vbuf));

    shv.shvnamelen = strlen(vname);
    shv.shvvaluelen= sizeof(vbuf);
    shv.shvcode = RXSHV_SYFET;
    shv.shvret   = 0;
    RexxVariablePool(&shv);

    style[index] = atol(shv.shvvalue.strptr);
    }

  gdImageSetStyle(im, (int *)style, sp);

  free(style);

  BUILDRXULONG(_Retstr, gdStyled);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageGetStyledBrushed(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{

  BUILDRXULONG(_Retstr, gdStyledBrushed);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageGetColor(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
ULONG   color;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im     = (gdImagePtr)atol(_Argv[0].strptr);
  color  = atol(_Argv[1].strptr);

  switch(_Name[9])
    {
    case 'G':
      color = gdImageGreen(im, color);
      break;
    case 'R':
      color = gdImageRed(im, color);
      break;
    case 'B':
      color = gdImageBlue(im, color);
      break;
    }

  BUILDRXULONG(_Retstr, color);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageGetPixel(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     x, y, color;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 3)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);
  x  = atol(_Argv[1].strptr);
  y  = atol(_Argv[2].strptr);


  BUILDRXULONG(_Retstr, gdImageGetPixel(im, x, y));

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageSxy(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     xy;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 1)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);

  if (_Name[10] == 'X')
    xy = gdImageSX(im);
  else
    xy = gdImageSY(im);

  BUILDRXULONG(_Retstr, xy);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageBoundsSafe(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     x, y;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 3)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);
  x  = atol(_Argv[1].strptr);
  y  = atol(_Argv[2].strptr);


  BUILDRXULONG(_Retstr, gdImageBoundsSafe(im, x, y));

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageGetTTI(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     rc;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 1)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im = (gdImagePtr)atol(_Argv[0].strptr);

  switch (_Name[12])
    {
    case 'o':
    case 'O':
      rc = gdImageColorsTotal(im);
      break;
    case 'I':
      rc = gdImageGetInterlaced(im);
      break;
    case 'T':
      rc = gdImageGetTransparent(im);
      break;
    }

  BUILDRXLONG(_Retstr, rc);

return(OK_CALL);
}


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageColorDeallocate(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     color;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  color = atol(_Argv[1].strptr);

  gdImageColorDeallocate(im, color);

  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageColorSet(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     color;
gdImagePtr      im;
                                        /* check arguments            */
  if (_Argc != 2)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  im    = (gdImagePtr)atol(_Argv[0].strptr);
  color = atol(_Argv[1].strptr);

  switch (_Name[9])
    {
    case 'C':
      gdImageColorTransparent(im, color);
      break;
    case 'I':
      gdImageInterlace(im, color);
      break;
    }


  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageCopy(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     dstX, dstY, srcX, srcY, w, h;
gdImagePtr      src, dst;
                                        /* check arguments            */
  if (_Argc != 8)                       /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  dst   = (gdImagePtr)atol(_Argv[0].strptr);
  src   = (gdImagePtr)atol(_Argv[1].strptr);
  dstX  = atol(_Argv[2].strptr);
  dstY  = atol(_Argv[3].strptr);
  srcX  = atol(_Argv[4].strptr);
  srcY  = atol(_Argv[5].strptr);
  w     = atol(_Argv[6].strptr);
  h     = atol(_Argv[7].strptr);

  gdImageCopy(dst, src, dstX, dstY, srcX, srcY, w, h);

  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
ULONG RxgdImageCopyResized(
  PSZ           _Name,                  /* name of the function         */
  ULONG         _Argc,                  /* number of args               */
  RXSTRING      _Argv[],                /* list of argument strings     */
  PSZ           _Queuename,             /* current queue name           */
  PRXSTRING     _Retstr)                /* returned result string       */
{
int     dstX, dstY, srcX, srcY, dstW, dstH, srcW, srcH;
gdImagePtr      src, dst;
                                        /* check arguments            */
  if (_Argc != 10)                      /* wrong number?              */
    return BAD_CALL;                    /* raise an error             */

  dst   = (gdImagePtr)atol(_Argv[0].strptr);
  src   = (gdImagePtr)atol(_Argv[1].strptr);
  dstX  = atol(_Argv[2].strptr);
  dstY  = atol(_Argv[3].strptr);
  srcX  = atol(_Argv[4].strptr);
  srcY  = atol(_Argv[5].strptr);
  dstW  = atol(_Argv[6].strptr);
  dstH  = atol(_Argv[7].strptr);
  srcW  = atol(_Argv[8].strptr);
  srcH  = atol(_Argv[9].strptr);

  gdImageCopyResized(dst, src, dstX, dstY, srcX, srcY, dstW, dstH, srcW, srcH);

  BUILDRXULONG(_Retstr, 0);

return(OK_CALL);
}

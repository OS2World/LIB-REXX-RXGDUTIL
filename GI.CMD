/* ---------------------------- */
/* Image File support code test */
/*                              */
/* GIF Info GI.CMD              */
/*                              */
/* Display some info  for the   */
/* GIF file                     */
/*                              */
/* ---------------------------- */
Call RxFuncAdd 'RxgdLoadFuncs', 'RXGDUTIL', 'RxgdLoadFuncs'
Call RxgdLoadFuncs

parse ARG cl

  im = RxgdImageCreateFromGIF(cl)

  IF (im == 1) THEN
    DO

    clGIF = cl || '.GIF'

    im = RxgdImageCreateFromGIF(clGIF)

    IF (im == 1) THEN
      DO
      Say 'File --->' || cl || '<--- not found.'
      RETURN
      END

    cl = cl || '.GIF'

    END

  Say 'GIF Information for ' cl
  Say ' '
  Say 'Image Handle     = ' im
  Say 'Total Colors     = ' RxgdImageColorsTotal(im)
  i = RxgdImageGetInterlaced(im)
  IF (i == 0) THEN
    InterL = 'No'
  else
    InterL = 'Yes'
  Say 'Interlaced       = ' InterL
  t = RxgdImageGetTransparent(im)
  if (t <> -1 ) THEN
     Say 'Transparent      = ' FORMAT(t, 3) '  Red=' FORMAT(RxgdImageRed(im, t),3) '  Blue=' FORMAT(RxgdImageBlue(im, t),3) '  Green=' FORMAT(RxgdImageGreen(im, t),3)
  Say ' '
  Say 'Width            = ' RxgdImageSX(im)
  Say 'Height           = ' RxgdImageSY(im)

  rc = RxgdImageDestroy(im)

Call RxgdUnloadFuncs

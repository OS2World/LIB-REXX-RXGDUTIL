/* ---------------------------- */
/* GD Supprot Rexx code         */
/*                              */
/* GI.CMD - Gif Set Interlaced  */
/*          BIT                 */
/*                              */
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

  Say 'GIF Information for ' cl || ' Handle=' || im
  Say ' '
  rc = RxgdImageInterlace(im, 1)
  rc = RxgdImageGIF(im, cl)
  rc = RxgdImageDestroy(im)

  Say 'Interlaced BIT set for file ' cl

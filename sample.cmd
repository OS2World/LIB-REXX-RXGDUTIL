/* Image File support code test */
/* Just a bunch of rexx calls   */
/* to test the code             */

Call RxFuncAdd 'RxgdLoadFuncs', 'RXGDUTIL', 'RxgdLoadFuncs'

Call RxgdLoadFuncs

  im = RxgdImageCreate(500, 350)
  say 'RxgdImageCreate rc = ' im
  en = RxgdImageCreateFromGIF("env.gif")
  say 'RxgdImageCreateFromGIF rc = ' en

  brush = RxgdImageSetBrush(im, en)
  say 'RxgdImageSetBrush brush = ' brush
  tile  = RxgdImageSetTile(im, en)
  say 'RxgdImageSetTile tile = ' tile

  s.0 = 0
  s.1 = 0
  s.2 = 0
  s.3 = 0
  s.4 = 0
  s.5 = 0
  s.6 = 0
  s.7 = 0
  s.8 = 0
  s.9 = 0
  s.10= 1
  styled  = RxgdImageSetStyle(im, s, 11)
  say 'RxgdImageSetStyle style = ' styled

  styledbrush  = RxgdImageGetStyledBrushed(im, s, 11)
  say 'RxgdImageGetStyleBrushed stylebrush = ' styledbrush

  black = RxgdImageColorAllocate(im, 0, 0, 0,)
  white = RxgdImageColorAllocate(im, 255, 255, 255)
  gray  = RxgdImageColorAllocate(im, 128, 128, 128)
  red   = RxgdImageColorAllocate(im, 255, 0, 0)
  green = RxgdImageColorAllocate(im, 0, 255, 0)
  blue  = RxgdImageColorAllocate(im, 0, 0, 255)

  rc = RxgdImageFill(im, 0, 0, gray)
  say 'RxgdImageFill rc = ' rc

  rc = RxgdImageSetPixel(im, 1, 1, black)
  say 'RxgdImageSetPixel rc = ' rc

  rc = RxgdImageLine(im, 200, 50, 450, 50, white)
  say 'RxgdImageLine rc = ' rc

  rc = RxgdImageLine(im, 200, 200, 300, 200, brush)
  say 'RxgdImageLine w/ brush rc = ' rc

  rc = RxgdImageLine(im, 220, 150, 275, 220, styledbrush)
  say 'RxgdImageLine w/ styledbrush rc = ' rc

  rc = RxgdImageFilledRectangle(im, 375, 200, 475, 300, tile)
  say 'RxgdImageFilledRectangle rc = ' rc

  poly.0 = 50
  poly.1 = 50
  poly.2 = 220
  poly.3 = 99
  poly.4 = 220
  poly.5 = 220
  poly.6 = 120
  poly.7 = 220
  rc = RxgdImagePolygon(im, poly, 4, blue)
  say 'RxgdImagePolygon rc = ' rc

  poly.0 = 50
  poly.1 = 0
  poly.2 = 99
  poly.3 = 99
  poly.4 = 0
  poly.5 = 99
  rc = RxgdImageFilledPolygon(im, poly, 3, green)
  say 'RxgdImagePolygon rc = ' rc

  rc = RxgdImageRectangle(im, 110, 110, 130, 130, red)
  say 'RxgdImageRectangle rc = ' rc

  rc = RxgdImageFilledRectangle(im, 140, 225, 170, 275, blue)
  say 'RxgdImageFilledRectangle rc = ' rc

  rc = RxgdImageArc(im,425,150, 77, 77, 0, 360, green)
  say 'RxgdImageArc rc = ' rc

  rc = RxgdImageString(im, 'T', 10, 10, 'Tiny Hello World', black)
  say 'RxgdImageString rc = ' rc
  rc = RxgdImageString(im, 'S', 10, 40, 'Small Hello World', black)
  say 'RxgdImageString rc = ' rc
  rc = RxgdImageStringUp(im, 'M', 475, 300, 'Med Bold Hello World', black)
  say 'RxgdImageStringUp rc = ' rc
  rc = RxgdImageString(im, 'L', 10, 100, 'Large Hello World', black)
  say 'RxgdImageString rc = ' rc
  rc = RxgdImageString(im, 'G', 10, 150, 'Giant Hello World', black)
  say 'RxgdImageString rc = ' rc


  rc = RxgdImageGIF(im, "AndyNEW.GIF")
  say 'RxgdImageGIF rc = ' rc

  rc = RxgdImageDestroy(im)
  say 'RxgdImageDestroy(im) = ' rc

  rc = RxgdImageDestroy(en)
  say 'RxgdImageDestroy(en) = ' rc

  Call RxgdUnloadFuncs
  Call RxFuncDrop 'RxgdLoadFuncs'

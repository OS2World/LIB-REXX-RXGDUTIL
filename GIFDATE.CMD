/* Image File support code test */

Call RxFuncAdd 'RxgdLoadFuncs', 'RXGDUTIL', 'RxgdLoadFuncs'

Call RxgdLoadFuncs

  ims = RxgdImageCreate(85, 40)
  imm = RxgdImageCreate(175, 60)
  iml = RxgdImageCreate(200, 100)


  sblack = RxgdImageColorAllocate(ims, 0, 0, 0,)
  swhite = RxgdImageColorAllocate(ims, 255, 255, 255)
  sgray  = RxgdImageColorAllocate(ims, 128, 128, 128)
  sred   = RxgdImageColorAllocate(ims, 255, 0, 0)
  sgreen = RxgdImageColorAllocate(ims, 0, 255, 0)
  sblue  = RxgdImageColorAllocate(ims, 0, 0, 255)

  mblack = RxgdImageColorAllocate(imm, 0, 0, 0,)
  mwhite = RxgdImageColorAllocate(imm, 255, 255, 255)
  mgray  = RxgdImageColorAllocate(imm, 128, 128, 128)
  mred   = RxgdImageColorAllocate(imm, 255, 0, 0)
  mgreen = RxgdImageColorAllocate(imm, 0, 255, 0)
  mblue  = RxgdImageColorAllocate(imm, 0, 0, 255)

  lblack = RxgdImageColorAllocate(iml, 0, 0, 0,)
  lwhite = RxgdImageColorAllocate(iml, 255, 255, 255)
  lgray  = RxgdImageColorAllocate(iml, 128, 128, 128)
  lmred  = RxgdImageColorAllocate(iml, 200, 64, 64)
  lgreen = RxgdImageColorAllocate(iml, 0, 255, 0)
  lblue  = RxgdImageColorAllocate(iml, 0, 0, 194)
  ldblue  = RxgdImageColorAllocate(iml, 0, 0, 128)
  lmblue  = RxgdImageColorAllocate(iml, 0, 128,  64)

  Call RxgdImageFill ims, 0, 0, sgray
  Call RxgdImageFill iml, 0, 0, lblue

  Call RxgdImageString ims, 'M', 3, 4, date(), sgreen
  Call RxgdImageString ims, 'M',13, 24, time(), swhite

  Call RxgdImageCopyResized imm, ims, 0,0, 0,0, 175, 60, 85, 40

  brush = RxgdImageSetBrush(iml, imm)
  Call RxgdImageLine iml, 100, 50, 100, 50, brush

  Call RxgdImageRectangle iml, 12, 20, 187, 80, lmblue
  Call RxgdImageRectangle iml, 11, 19, 186, 79, lmblue

                /*          X,   Y,   X,   Y  Color  */
  Call RxgdImageLine iml,   0,   0,  11,  20, lmblue
  Call RxgdImageLine iml,   1,   0,  12,  20, lmblue
  Call RxgdImageLine iml,   0, 100,  11,  80, lmblue
  Call RxgdImageLine iml,   1, 100,  12,  80, lmblue
  Call RxgdImageLine iml, 186,  80, 199, 100, lmblue
  Call RxgdImageLine iml, 187,  80, 200, 100, lmblue
  Call RxgdImageLine iml, 186,  20, 199,   0, lmblue
  Call RxgdImageLine iml, 187,  20, 200,   0, lmblue

  Call RxgdImageFill iml, 190, 90, ldblue
  Call RxgdImageFill iml, 198, 90, ldblue

  Call RxgdImageString iml, 'S', 70,  7, 'AB SoftWare', lmred

  Call RxgdImageInterlace iml, 1
/*Call RxgdImageColorTransparent iml, lgray */

  Call RxgdImageGIF iml, "GIFDate.GIF"

  Call RxgdImageDestroy ims
  Call RxgdImageDestroy imm
  Call RxgdImageDestroy iml

  Say 'All Done!'

  Call RxgdUnloadFuncs
  Call RxFuncDrop 'RxgdLoadFuncs'

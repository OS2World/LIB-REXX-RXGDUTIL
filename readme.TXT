Hi and welcome to RXGDUTIL - The Rexx extensions to support building
GIF files.  My name is Andy Wysocki (awysocki@bearsoft.com)  I found
this great GD support code to build GIF files.  But since I am hooked
on REXX I wanted to build GIF files from REXX.  So I created the
Rxgdutil.C support module for REXX.  You take this code AS-IS and no
warrenty is implied.  I provide the RXGDUTIL.DLL already made so you don't
really need the rest of the stuff, but its here just incase you find a
bug or want to add some functions.

 To test the .DLL you can just run the SAMPLE.CMD file and it will create
an .GIF file called ANDYNEW.GIF  Thats all there is to it.  You can play
around with the sample .CMD file to see what all the function do.  I am
not a graphics person so my sample code is not very exciting.   So on with
the rest of the RXGDUTIL manual.

  This is a QUICKLY typed up a REXX manual.  To understand completely all
the 'gd' function I would suggest looking the gd.zip file and looking at the
.HTML document.  Or better yet viewing they GD home page.

http://sunsite.unc.edu/boutell/index.html

Tom has a bunch of other libraries/support code to help with other functions
in life, I would suggest also checking them out.

-------------------------------
Installation:

If you already unzip'ed this module then you have installed it.  If you plan
on using these functions, then you MUST put the RXGDUTIL.DLL in a directory
that is in your LIBPATH or always run the REXX .CMD files from the directory
where the RXGDUTIL.DLL is.


-------------------------------
Legal Stuff:


gd 1.2 is copyright 1994, 1995, Quest Protein Database Center,
Cold Spring Harbor Labs. Permission granted to copy and distribute
this work provided that this notice remains intact. Credit
for the library must be given to the Quest Protein Database Center,
Cold Spring Harbor Labs, in all derived works. This does not
affect your ownership of the derived work itself, and the intent
is to assure proper credit for Quest, not to interfere with your
use of gd. If you have questions, ask. ("Derived works"
includes all programs that utilize the library. Credit must
be given in user-visible documentation.)

If you wish to release modifications to gd,
please clear them first by sending email to
boutell@boutell.com; if this is not done, any modified version of the gd
library must be clearly labeled as such.

The Quest Protein Database Center is funded under Grant P41-RR02188 by
the National Institutes of Health.

Written by http://sunsite.unc.edu/boutell/index.html  Thomas Boutell 2/94-7/95

The GIF compression code is based on that found in the pbmplus
utilities, which in turn is based on GIFENCOD by David Rowley. See the
notice below:


/*
** Based on GIFENCOD by David Rowley <mgardi@watdscu.waterloo.edu>.A
** Lempel-Zim compression based on "compress".
**
** Modified by Marcel Wijkstra <wijkstra@fwi.uva.nl>
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** The Graphics Interchange Format(c) is the Copyright property of
** CompuServe Incorporated.  GIF(sm) is a Service Mark property of
** CompuServe Incorporated.
*/



The GIF decompression is based on that found in the pbmplus
utilities, which in turn is based on GIFDECOD by David Koblas. See the
notice below:

/* +-------------------------------------------------------------------+ */
/* | Copyright 1990, 1991, 1993, David Koblas.  (koblas@netcom.com)    | */
/* |   Permission to use, copy, modify, and distribute this software   | */
/* |   and its documentation for any purpose and without fee is hereby | */
/* |   granted, provided that the above copyright notice appear in all | */
/* |   copies and that both that copyright notice and this permission  | */
/* |   notice appear in supporting documentation.  This software is    | */
/* |   provided "as is" without express or implied warranty.           | */
/* +-------------------------------------------------------------------+ */


And don't forget that Andrew J. Wysocki (Andy) wrote the RXGDUTIL.C
module and should get all credit where credit is due. September 1995



-------------------------------
Whats all Here:

Since I am using somebody else's code for the GIF stuff, I have included
a .ZIP file in my zip file.  The original file was a TAR.Z file but I un-TARed
it and just .ZIP'ed it back up.  The GD code I have included is version 1.2
If you never plan on building the GD.LIB then you don't have to unzip the
GD12.ZIP file.  It does have more README's and other 'C' sample code, so
if this don't explain it well, then you can unzip their stuff and give it a
look see.

  gd.lib        - The library I made from the GD12.ZIP file
  gd.dep        - Dependency file for making the GD.LIB file
  gd.mak        - Make file to compile the GD12.ZIP file to OBJ's
  gd12.zip      - ORIGINAL Version 1.2 of gd.tar.Z
  gdlib.cmd     - Command file to create the GD.LIB from the OBJ's
  RXGDUTIL.C    - Rexx 'C' source code to call the GD.LIB functions
  rxgdutil.def  - Exports of the functions from RXGDUTIL.DLL
  RXGDUTIL.DEP  - Dep file for building RXGDUTIL.DLL
  RXGDUTIL.MAK  - Make file to put it all together
  MM.CMD        - Command file to build .OBJ's and .DLL

  GI.CMD        - Graphic Info, Sample stuff for displaying GIF info

  sample.cmd    - Stupid sample code to build a GIF file
  env.gif       - .GIF file used as a brush in sample.cmd
  SETINT.CMD    - Set the Interlace bit in a .GIF file
  GIFDate.cmd   - Create a GIF file with the current date & time


-------------------------------
Support

You can reach me the author of 'RXGDUTIL' at
http://www.bearsoft.com/abs/rxgdutil.html
awysocki@bearsoft.com

You can reach the author of 'gd' at
http://sunsite.unc.edu/boutell/index.html
http://siva.cshl.org/gd/gd.html
boutell@boutell.com


-------------------------------
Function calls:

im=RxgdImageCreate(x, y)
   - Create an image in memory
   x - How wide
   y - How tall

   im - Returned Image Handle (1 = Not created, anything else is GOOD)


   ...
   im = RxgdImageCreate(100, 50)
   ...

im=RxgdImageCreateFromGIF(filename)
   - Create and image from a GIF file
   filename - Gif Path and file name

   im - Returned image handle

   ...
   im = RxgdImageCreateFromGIF("env.gif")
   ...


RxgdImageDestroy(im)
   - Release the Image from Memory (*** THIS IS A MUST DO ***)

   im - The image file to release

   ...
   Call RxgdImageDestroy im
   ...


RxgdImageGIF(filename)
   - Write a GIF file from Memory to a flat file

   filename - is the file name to save the image as

   ...
   Call RxgdImageGIF "Andy.GIF"
   ...


RxgdImageSetPixel(im, x, y, color)
   - Set a specific Pixel to a color index

   im - Image file handle
   x - X coordinate of the pixel
   y - Y coordinate of the pixel
   color - Color index to use 0 - 255

   ...
   Call RxgdImageSetPixel im 100 150 185
   ...


RxgdImageLine(im, x1, y2, x2, y2, color)
   - Draw a line between two end points

   im - Image file handle
   x1 - X coordinate of the start point
   y1 - Y coordinate of the start point
   x2 - X coordinate of the end point
   y2 - Y coordinate of the end point
   color - Color Index to use (0-255)


RxgdImagePolygon(im, points, pointsTotal, color)
   - Draw a poloygon with the verticies (at least 3)
RxgdImageFilledPolygon(im, points, pointsTotal Color)
   - Draw a Poloygon with the Verticies and fill it with the color

   im - Image file handle
   points - STEM Variable with a minimun of 3 sets of points
   pointsTotal - Number of SETS in the points STEM variable
   color - Color Index to use


RxgdImageRectangle(im, x1, y1, x2, y2, color)
   - Draw a rectangle with the two corners (upper left first, then lower right)
RxgdImageFilledRectangle(im, x1, y1, x2, y2, color)
   - Draw a rectangle with the two corners (upper left first, then lower right)
     and fill it with the color

   im - Image file handle
   x1, y1 - Upper left corner
   x2, y2 - Lower right corner
   color - Color Index to use


RxgdImageArc(im, cx, cy, w, h, s, e, color)
   - Draw and ARC or CIRCLE with the given points
     To draw a circle use (im, 100, 100, 25, 25, 0, 360)
     To draw a arc    use (im, 100, 100, 50, 25, 0, 180)

   im - Image file handle
   cx, cy - Starting X & Y Points
   w - Width
   h - Height
   s - Degrees Starting Point (0-360)
   e - Degrees Ending Poing (0-360)

RxgdImageFillToBorder(im, x, y, border, color)
   - Flood a portion of the image with the specified color

   im - Image file handle
   x, y - Starting point (pixel)
   border - Stopping point by color
   color - Color to fill in


RxgdImageFill(im, x, y, color)
   - Floods a portion of the image with the specified color

   im - Image file handle
   x, y - starting point
   color - Color to use for the fill/flood


brush=RxgdImageSetBrush(im, imbrush)
   - Allow you to use another image as a brush to paint a whole picture at once

   im - Image file handle that will use the brush
   imbrush - Image file handle that will be used as the brush
   brush - Brush Image file handle


tile=RxgdImageSetTile(im, imtile)
   - Allow you to use another image to tile the GIF image

   im - Image file handle that will be used to tile
   imtile - Image file handle that will be used as the tile
   tile - Tile Image file handle


style=RxgdImageSetStyle(im, stylestem, styleLength)
   - Allows you to specify pixels for drawing dashed lines and other colorful
     stuff

   im - Image file handle
   stylestem - Stem variable with bit/brush pattern
   styleLength - number of bit/pixel patterns
   style - Style Image file handle


stylebrush=RxgdImageGetStyleBrushed(im)
   - Allows you to get the Styled Brushed image handle

   im - Image file handle
   stylebrush - StyleBrushed Image file handle


blue=RxgdImageBlue(im, color)
   - Retrieves the BLUE portion of the color index

   im - Image file handle
   color - color index to retrieve blue color
   blue - Blue portion of the color (0-255)

red=RxgdImageRed(im, color)
   - Retrieves the RED portion of the color index

   im - Image file handle
   color - color index to retrieve red color
   red - Red portion of the color (0-255)

green=RxgdImageGreen(im, color)
   - Retrieves the GREEN portion of the color index

   im - Image file handle
   color - color index to retrieve green color
   green - Green portion of the color (0-255)


pixel=RxgdImageGetPixel(im, x, y)
   - Retrieve the Color Index of the pixel

   im - Image file handle
   x, y - Pixel location
   pixel - Color index of the pixel


sx=RxgdImageSX(im)
sy=RxgdImageSY(im)
   - Retrieve the X & Y size of the Image

   im - Image file handle
   sx - Width of the image
   sy - Height of the image


RxgdImageString(im, font, x, y, s, color)
   - Print some text onto the GIF file at the specified location
RxgdImageStringUp(im, font, x, y, s, color)
   - Print some text rotated at 90 degrees onto the GIF file at the
     specified location

   im - Image file handle
   font - Font type currently 'T'iny, 'S'mall, 'M'ediumBold,
          'L'arge, or 'G'iant
   x, y - Location to start at
   s - String to use
   color - Color index to use for characters


color=RxgdImageColorAllocate(im, r, g, b)
   - Allocate the first available color index in the image with the specified
     color, if the (256) color table is full this will return -1

   im - Image file handle
   r - Red Color 0-255
   g - Green color 0-255
   b - Blue Color 0-255
   color - Returned color index


color=RxgdImageColorClosest(im, r, g, b)
   - Find a color in the color table that is closest to the colors specified
color=RxgdImageColorExact(im, r, g, b)
   - Find a color in the color table that is an exact match to the
     colors specified

   im - Image file handle
   r - Red color 0-255
   g - Green color 0-255
   b - Blue color 0-255
   color - returned color index if found -1 if not found


total=RxgdImageColorsTotal(im)
   - Return the number of colors in the color table

   im - Image file handle
   total - the total number of colors in the color table


interlace=RxgdImageGetInterlaced(im)
   - Return if the image is interlaced or not

   im - Image file handle
   interlace - returned value 1=Interlaced, 0=Not Interlaced


RxgdImageInterlaced(im, interlace)
   - Return if the image is interlaced or not

   im - Image file handle
   interlace - 1=Interlaced, 0=Not Interlaced


color=RxgdImageGetTransparent(im)
   - Return the color index of the transparent color

   im - Image file handle
   color - Returned color index of the color that is treated as Transparent


RxgdImageColorTransparent(im, color)
   - Return the color index of the transparent color

   im - Image file handle
   color - Color index of the color that is treated as Transparent


RxgdImageColorDeallocate(im, color)
   - Remove a color from the color table and leave the entry as usable

   im - Image file handle
   color - Color index of the color to deallocate


RxgdImageCopy(imdest, imsrc, destX, destY, srcX, srcY, w, h)
   - Copy a rectangular portion of one image to another image


   imdest - Destination Image file handle
   imsrc  - Source Image file handle
   destX, destY - Destination starting point
   srcX, srcY - Source starting point
   w, h - Width and Height of the rectangle to copy.


RxgdImageCopyResized(imdest, imsrc, destX, destY, srcX, srcY,
                     destW, destH, srcW, srcH)
   - Copy a rectangular portion of one image to another image.  The
     destination region can vary, resulting in stretching or shrinking the
     size of the image

   imdest - Destination Image file handle
   imsrc - Source Image file handle
   destX, destY - Destination stating point
   srcX, srcY - Source starting point
   destW, destH - Destination Width and Height
   srcW, srcH - Source Width and Height

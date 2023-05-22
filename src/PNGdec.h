//
// PNG Decoder
//
// written by Larry Bank
// bitbank@pobox.com
// Arduino port started 5/3/2021
// Original PNG code written 20+ years ago :)
// The goal of this code is to decode PNG images on embedded systems
//
// Copyright 2021 BitBank Software, Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//===========================================================================
//

#ifndef __PNGDEC__
#define __PNGDEC__

#include "png.h"

//
// The PNG class wraps portable C code which does the actual work
//
class PNG
{
  public:
    int openRAM(uint8_t *pData, int iDataSize, PNG_DRAW_CALLBACK *pfnDraw);
    int openFLASH(uint8_t *pData, int iDataSize, PNG_DRAW_CALLBACK *pfnDraw);
    int open(const char *szFilename, PNG_OPEN_CALLBACK *pfnOpen, PNG_CLOSE_CALLBACK *pfnClose, PNG_READ_CALLBACK *pfnRead, PNG_SEEK_CALLBACK *pfnSeek, PNG_DRAW_CALLBACK *pfnDraw);
    void close();
    int decode(void *pUser, int iOptions);
    int getWidth();
    int getHeight();
    int getBpp();
    int hasAlpha();
    uint32_t getTransparentColor();
    int isInterlaced();
    uint8_t * getPalette();
    int getPixelType();
    int getLastError();
    int getBufferSize();
    uint8_t *getBuffer();
    void setBuffer(uint8_t *pBuffer);
    uint8_t getAlphaMask(PNGDRAW *pDraw, uint8_t *pMask, uint8_t ucThreshold);
    void getLineAsRGB565(PNGDRAW *pDraw, uint16_t *pPixels, int iEndianness, uint32_t u32Bkgd);

  private:
    PNGIMAGE _png;
};

#endif // __PNGDEC__

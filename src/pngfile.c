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
#include "png.h"
#include "zlib.h"

static int32_t readFile(PNGFILE* pFile, uint8_t* pBuf, int32_t iLen)
{
    return (int32_t)fread(pBuf, 1, iLen, (FILE*)pFile->fHandle);
}
static int32_t seekFile(PNGFILE* pFile, int32_t iPosition)
{
    return (int32_t)fseek((FILE*)pFile->fHandle, iPosition, SEEK_SET);
}

static void closeFile(PNGFILE* pFile)
{
    fclose((FILE*)pFile->fHandle);
}


int PNG_openFile(PNGIMAGE *pPNG, const char *szFilename, PNG_DRAW_CALLBACK *pfnDraw)
{
    pPNG->iError = PNG_SUCCESS;
    pPNG->pfnRead = readFile;
    pPNG->pfnSeek = seekFile;
    pPNG->pfnDraw = pfnDraw;
    pPNG->pfnOpen = NULL;
    pPNG->pfnClose = closeFile;
    pPNG->PNGFile.fHandle = fopen(szFilename, "r+b");
    if (pPNG->PNGFile.fHandle == NULL)
       return 0;
    fseek((FILE *)pPNG->PNGFile.fHandle, 0, SEEK_END);
    pPNG->PNGFile.iSize = (int)ftell((FILE *)pPNG->PNGFile.fHandle);
    fseek((FILE *)pPNG->PNGFile.fHandle, 0, SEEK_SET);
    return PNG_init(pPNG);
} /* PNG_openFile() */


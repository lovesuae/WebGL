//--------------------------------------------------------------
//
// Microsoft Edge Implementation
// Copyright(c) Microsoft Corporation
// All rights reserved.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files(the ""Software""),
// to deal in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//--------------------------------------------------------------
#include "PreComp.hxx"

class CGLSLPreParser;              // Forward define for lexer header to compile

#include "pre.tab.h"           // We need this to include the lexer header

#pragma warning(disable:28718)
#include "lex.pre.h"           // We need this for the scanner type definitions

#include "GLSLPreParser.hxx"

//+----------------------------------------------------------------------------
//
//  Function:   GLSLPreInput
//
//  Synopsis:   Global function called for pulling input into the parser. Used
//              instead of a stdin stream by the tokenizer.
//
//-----------------------------------------------------------------------------
int GLSLPreInput(__in CGLSLPreParser* pParser, __out_ecount(1) char* buf, int /*max_size*/)
{
    return pParser->UseInput()->PullInput(buf);
}

//+-----------------------------------------------------------------------------
//
//  Function:   GLSLPreerror
//
//  Synopsis:   Called from the parser and lexer when an error is encountered.
//
//------------------------------------------------------------------------------
void GLSLPreerror(__in YYLTYPE* pLocation, yyscan_t scanner, __in_z_opt const char* pszErrorText)
{
    CGLSLPreParser* pParser = GLSLPreget_extra(scanner);

    pParser->NotifyError(pLocation, pszErrorText);
}

//+-----------------------------------------------------------------------------
//
//  Function:   GLSLPreUpdateLocation
//
//  Synopsis:   Called as a user action to record the position of tokens.
//
//------------------------------------------------------------------------------
void GLSLPreUpdateLocation(__in CGLSLPreParser* pParser, __in YYLTYPE* pLocation, int lineNo, int tokenLength)
{
    pParser->UpdateLocation(pLocation, lineNo, tokenLength);
}

//+-----------------------------------------------------------------------------
//
//  Function:   GLSLPrewrap
//
//  Synopsis:   Called when input is exhausted to determine next action. We
//              always want to finish at this point.
//
//------------------------------------------------------------------------------
int GLSLPrewrap(yyscan_t)
{
    return 1;
}

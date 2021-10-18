#pragma once

enum ETraversalMethod
{
    Sequential,
    Inverted
};

enum ELinkNodeEqual
{
    ValueRequired,
    LastPtrRequired,
    NextPtrRequired
};

enum EPolynomialInsertSituation
{
    BeforeHead,
    InMiddle,
    AfterTair,
    ExponentFound
};

enum EExponentsCompare
{
    Larger,
    Equal,
    Smaller
};

enum EBracketsSituation
{
    LeftOverflow,
    Valid,
    RightOverflow
};
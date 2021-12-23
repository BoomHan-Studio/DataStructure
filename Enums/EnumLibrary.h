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

enum ELinesRelation
{
    Parallel,
    Intersecting,
    Perpendicular
};

enum ETreeNodeChildDirection
{
    Left = 'L',
    Right = 'R'
};

enum EBinaryTreeTraverseMethod
{
    Sequence,
    Secondary,
    Rear,
	Level
};

enum EDebugLevel
{
    Log,
    Warning,
    Error
};
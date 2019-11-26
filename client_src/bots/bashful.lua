local UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT = 0, 1, 2, 3, 4, 5, 6, 7
local moves = {
    UP, UP, UP, UP, UP, UP, UP,
    UPRIGHT, UPRIGHT, RIGHT, UP, UP, UP, UP,
    UPLEFT, UPLEFT, LEFT, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
    UPLEFT, UPLEFT, LEFT, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
    UPLEFT, UPLEFT, LEFT, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
    UPLEFT, UPLEFT, LEFT, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
}

getMove = function(args)
    return moves[args[1]]
end

getSize = function(args)
    return #moves
end
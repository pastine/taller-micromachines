local UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT = 0, 1, 2, 3, 4, 5
local moves = {
    UP, UP, LEFT, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP,
    LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,
    DOWN, DOWN, DOWN, UPLEFT, LEFT, LEFT,
}

getMove = function(args)
    return moves[args[1]]
end

getSize = function(args)
    return #moves
end
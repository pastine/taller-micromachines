local UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT = 0, 1, 2, 3, 4, 5
local moves = {UP, LEFT}

getMove = function(args)
    return moves[args[1]]
end

getSize = function(args)
    return #moves
end
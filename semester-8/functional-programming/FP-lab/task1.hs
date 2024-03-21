module Main where
import qualified Data.Set as Set

boardSize :: Int
boardSize = 8

superSet = Set.fromList [(x,y) | x <- [1..boardSize], y <- [1..boardSize]]

moves :: (Int, Int) -> [(Int, Int)]
moves (row, column) = 
    let possibleMoves = [1,2,-1,-2] in
    filter (\(x,y) -> x > 0 && y > 0 && x < (boardSize + 1) && y < boardSize + 1) $
    map (\(f,g) -> (f row, g column)) 
        [((+x), (+y)) | x <- possibleMoves, y <- possibleMoves, (abs x) /= (abs y)]

pathBreaksGraph :: (Set.Set (Int, Int)) -> Bool
pathBreaksGraph used = 
        Set.size set1 /= boardSize * boardSize where
            unused = superSet Set.\\ used
            set1 = findAllNeighbours used minEl
            minEl = if Set.size unused == 0 then Nothing else Just (Set.findMin unused) 
            
findAllNeighbours :: (Set.Set (Int, Int)) -> Maybe (Int, Int) -> (Set.Set (Int, Int))
findAllNeighbours used Nothing      = used 
findAllNeighbours used (Just (x,y)) = neigh' used [(x,y)] where 
        neigh' used [] = used
        neigh' used (x:xs) = if not (Set.member x used) then 
                                    neigh' (Set.insert x used) (xs++(moves x))
                                else 
                                    neigh' used xs

pathThroughThemAll :: Int -> (Int, Int) -> [(Int, Int)]
pathThroughThemAll nn (x,y) = fst $ go 0 [] Set.empty (x,y) where 
    go :: Int -> [(Int, Int)] -> Set.Set (Int, Int) -> (Int, Int) -> ([(Int, Int)],Bool)
    go n path st position | n == nn = (path, True) 
                          | otherwise = 
        if pathBreaksGraph st then 
            ([], False)
        else
            case 
                (dropWhile (\(_,res) -> not res) $
                map (\x -> go (n+1) (position:path) (Set.insert position st) x) $
                filter (flip Set.notMember st) $
                moves position) 
            of
            [] -> ([], False)
            (x:_) -> x 

route60 :: Set.Set (Int, Int)
route60 = Set.fromList [(2,5),(1,3),(3,2),(1,1),(2,3),(1,5),(2,7),(4,8),(3,6),
    (5,5),(4,7),(2,8),(1,6),(3,5),(1,4),(2,2),(4,3),(2,4),(1,2),(3,1),
    (5,2),(3,3),(4,1),(5,3),(6,1),(4,2),(3,4),(2,6),(3,8),(5,7),(4,5),
    (3,7),(5,8),(4,6),(5,4),(6,2),(8,1),(7,3),(8,5),(7,7),(6,5),(8,4),
    (7,2),(6,4),(8,3),(7,1),(6,3),(8,2),(7,4),(8,6),(7,8),(6,6),(8,7),
    (7,5),(6,7),(8,8),(7,6),(6,8),(5,6),(4,4)]

main :: IO ()
main = do
    putStrLn $ show $ filter (\x -> not (x `elem`(t))) [(r,c) | r <- [1..8], c <- [1..8]] where t = pathThroughThemAll 60 (4,4)

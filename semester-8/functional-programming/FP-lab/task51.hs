module Main where

insertEdge :: [(Int, [Int])] -> Int -> Int -> [(Int, [Int])]
insertEdge [] from to = [(from, [to])]
insertEdge ((cur, adj):vers) from to | cur < from = (cur, adj) : (insertEdge vers from to)
                                     | cur == from = (cur, insertEdgeIntoVertex adj to) : vers
                                     | otherwise =  ((from), [(to)]) : (cur, adj) : vers 
    where
    insertEdgeIntoVertex [] to = [to]
    insertEdgeIntoVertex (a : adj) to | a < to = a : insertEdgeIntoVertex adj to 
                                      | a > to = to : a : adj
                                      | otherwise = (a: adj)


buildOrientedGraphFromList :: [(Int, Int)] -> [(Int, [Int])]
buildOrientedGraphFromList ls = go ([]) ls where 
    go g [] = g
    go (verts) ((from, to) : xs) = 
        go (insertEdge verts from to) xs

buildGraphFromList :: [(Int, Int)] -> [(Int, [Int])]
buildGraphFromList ls = go ([]) ls where 
    go g [] = g
    go (verts) ((from, to) : xs) = 
        go (insertEdge (insertEdge verts from to) to from) xs

allPaths :: [(Int, [Int])] -> Int -> Int -> [[Int]]
allPaths ([]) from to = [[]]
allPaths graph@((curr@(cur, adj):ver)) from to | cur > from  = [[]]
                                               | cur == from = go graph curr [] to
                                               | otherwise   = allPaths (ver) from to
        where 
            go gr (cur, adj) path to | cur == to = [reverse (cur:path)]
                                     | otherwise = concatMap (\x -> go gr (findInGraph gr x) (cur:path) to) $ notVisited adj path 
            notVisited [] path = []
            notVisited (x : vers) path = let rest = notVisited vers path in 
                                            if (elem x path) then rest else x : rest
            findInGraph ([]) x = (x, [])
            findInGraph ((cur_v@(cur, adj) : rest)) x = if cur == x then cur_v else findInGraph rest x

graph :: [(Int, [Int])]
graph = buildGraphFromList [(1,2),(2,3),(1,3),(3,4),(2,4), (4,5)]

main :: IO()
main = do
    putStrLn $ show $ allPaths graph 1 5
    
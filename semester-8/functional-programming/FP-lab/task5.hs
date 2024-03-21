module Main where
import Data.List (intercalate)

newtype Vertex = V Int deriving Show
newtype Graph = G [(Vertex, [Vertex])] deriving Show

insertEdge :: [(Vertex, [Vertex])] -> Int -> Int -> [(Vertex, [Vertex])]
insertEdge [] from to = [((V from), [(V to)])]
insertEdge ((V cur, adj):vers) from to | cur < from  = (V cur, adj) : (insertEdge vers from to)
                                       | cur == from = (V cur, insertEdgeIntoVertex adj to) : vers
                                       | otherwise   =  ((V from), [(V to)]) : (V cur, adj) : vers 
    where
    insertEdgeIntoVertex [] to = [V to]
    insertEdgeIntoVertex (V a : adj) to | a < to    = V a : insertEdgeIntoVertex adj to 
                                        | a > to    = V to : V a : adj
                                        | otherwise = (V a: adj)


buildOrientedGraphFromList :: [(Int, Int)] -> Graph
buildOrientedGraphFromList ls = go (G []) ls where 
    go g [] = g
    go (G verts) ((from, to) : xs) = 
        go (G $ insertEdge verts from to) xs

buildGraphFromList :: [(Int, Int)] -> Graph
buildGraphFromList ls = go (G []) ls where 
    go g [] = g
    go (G verts) ((from, to) : xs) = 
        go (G $ insertEdge (insertEdge verts from to) to from) xs

allPaths :: Graph -> Int -> Int -> [[Int]]
allPaths (G []) from to = [[]]
allPaths graph@(G (curr@(V cur, adj):ver)) from to | cur > from  = [[]]
                                                   | cur == from = go graph curr [] to
                                                   | otherwise   = allPaths (G ver) from to
        where 
            go gr (V cur, adj) path to | cur == to = [reverse (cur:path)]
                                       | otherwise = concatMap (\x -> go gr (findInGraph gr x) (cur:path) to) $ notVisited adj path 
            notVisited [] path = []
            notVisited (V x : vers) path = let rest = notVisited vers path in 
                                            if (elem x path) then rest else (V x) : rest
            findInGraph (G []) x = (x, [])
            findInGraph (G (cur_v@(V cur, adj) : rest)) (V x) = if cur == x then cur_v else findInGraph (G rest) (V x)

graph1 :: Graph
graph1 = buildOrientedGraphFromList [(1,2),(2,3),(1,3),(3,4),(3,5)]
graph2 :: Graph
graph2 = buildGraphFromList [(1,2),(2,3),(1,3),(3,4),(2,4),(4,5)]

visualizePaths :: [[Int]] -> [String]
visualizePaths = map ((intercalate "->") . (map show))

main :: IO()
main = do
    putStrLn $ show $ graph1
    putStrLn $ show $ graph2
    putStrLn $ show $ visualizePaths $ allPaths graph2 1 5
    
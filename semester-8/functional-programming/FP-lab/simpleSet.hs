module SimpleSet where

data Color = Red | Black

data RedBlackNode a = Nil 
                    | Node Color a (RedBlackNode a) (RedBlackNode a)

type Set a = RedBlackNode a

findSet ::(Eq a, Ord a) => (Set a) -> a -> Bool
findSet Nil _ = False
findSet (Node _ val left right) x = if val == x then True else 
                                        if val < x then findSet left x else findSet right x



leftRotate :: (Eq a, Ord a) => (RedBlackNode a) -> RedBlackNode a
leftRotate (Node cy vy (Node cx vx al bt) gm) = Node cx vx al (Node cy vy bt gm)
leftRotate x = x

rightRotate :: (Eq a, Ord a) => (RedBlackNode a) -> RedBlackNode a
rightRotate (Node cx vx al (Node cy vy bt gm)) = Node cy vy (Node cx vx al bt) gm
rightRotate x = x


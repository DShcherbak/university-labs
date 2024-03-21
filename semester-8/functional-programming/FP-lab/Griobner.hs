module Griobner where
import Data.List

data Monom c a = M c [a] deriving (Eq)

instance (Eq c, Ord a) => Ord (Monom c a) where
    compare (M _ asl) (M _ asr) = compare asl asr

instance (Show a, Show c, Num a, Num c, Eq a, Eq c) => Show (Monom c a) where
    show (M c as) = (if c == 1 then "" else show c) ++ 
                    (intercalate "*" $ map showOne $ (filter (\(p,_) -> p /= 0) $ zip as [1..]))
        where showOne (p,i) = "x" ++ (show i) ++ (if p == 1 then "" else "^" ++ (show p))

newtype Polynom c a = P [Monom c a] deriving (Eq)

instance (Show a, Show c, Num a, Num c, Eq a, Eq c) => Show (Polynom c a) where
    show (P ms) = intercalate " + " $ map show ms

lt :: Polynom c a -> Monom c a
lt (P as) = head as

zero :: (Num c, Eq c) => Monom c a -> Bool
zero (M c _) = c == 0

zeroP :: Polynom c a -> Bool
zeroP (P as) = null as

scale :: (Num c) => c -> Monom c a -> Monom c a
scale c' (M c as) = M (c*c') as

similar :: (Eq a) => Monom c a -> Monom c a -> Bool
similar (M _ asl) (M _ asr) = asl == asr

addSimilar :: (Num c) => Monom c a -> Monom c a -> Monom c a
addSimilar (M cl as) (M cr _) = M (cl+cr) as

mulMono :: (Num a, Num c) => Monom c a -> Monom c a -> Monom c a
mulMono (M cl asl) (M cr asr) = M (cl*cr) (zipWith (+) asl asr)


addPoly :: (Eq a, Eq c, Num c, Ord a) => Polynom c a -> Polynom c a -> Polynom c a
addPoly (P l) (P r) = P $ go l r
    where 
          go [] [] = []
          go as [] = as
          go [] bs = bs
          go left@(a:as) right@(b:bs) = 
              if similar a b then
                  if (zero $ ab) then
                      go as bs
                  else
                      (ab):(go as bs)
              else
                  if a > b then
                      a:(go as right)
                  else
                      b:(go left bs)
                    where ab = addSimilar a b

mulPM :: (Ord a, Eq c, Num a, Num c) => Polynom c a -> Monom c a -> Polynom c a
mulPM (P as) m = P $ map (mulMono m) as

mulM :: (Eq c, Num c, Num a, Ord a) => Polynom c a -> Polynom c a -> Polynom c a
mulM l@(P ml) r@(P mr) = foldl' addPoly (P []) $ map (mulPM r) ml

dividable :: (Ord a) => Monom c a -> Monom c a -> Bool
dividable (M _ al) (M _ ar) = and $ zipWith (>=) al ar

divideM :: (Fractional c, Num a) => Monom c a -> Monom c a -> Monom c a
divideM (M cl al) (M cr ar) = M (cl/cr) (zipWith (-) al ar)

reducable :: (Ord a) => Polynom c a -> Polynom c a -> Bool
reducable l r = dividable (lt l) (lt r)

reduce :: (Eq c, Fractional c, Num a, Ord a) =>
          Polynom c a -> Polynom c a -> Polynom c a
reduce l r = addPoly l r'
    where r' = mulPM r (scale (-1) q)
          q = divideM (lt l) (lt r)

reduceMany :: (Eq c, Fractional c, Num a, Ord a) =>
              Polynom c a -> [Polynom c a] -> Polynom c a
reduceMany h fs = if reduced then reduceMany h' fs else h'
    where (h', reduced) = reduceStep h fs False
          reduceStep h (f:fs) r 
              | zeroP h = (h, r)
              | otherwise = if reducable h f then
                                (reduce h f, True)
                            else
                                reduceStep h fs r
          reduceStep h [] r = (h, r)

lcmM :: (Num c, Ord a) => Monom c a -> Monom c a -> Monom c a
lcmM (M cl al) (M cr ar) = M (cl*cr) (zipWith max al ar)


makeSPoly :: (Eq c, Fractional c, Num a, Ord a) =>
             Polynom c a -> Polynom c a -> Polynom c a
makeSPoly l r = addPoly l' r'
    where l' = mulPM l ra
          r' = mulPM r la
          lcm = lcmM (lt l) (lt r)
          ra = divideM lcm (lt l)
          la = scale (-1) $ divideM lcm (lt r)


checkOne :: (Eq c, Fractional c, Num a, Ord a) =>
            Polynom c a -> [Polynom c a] -> [Polynom c a] -> [Polynom c a]
checkOne f checked@(c:cs) add = if zeroP s then
                                   checkOne f cs add
                               else
                                   s:(checkOne f cs (add ++ [s]))
    where s = reduceMany (makeSPoly f c) (checked++add)
checkOne _ [] _ = []


build :: (Fractional c, Ord a, Eq c, Num a) => [Polynom c a] -> [Polynom c a] -> [Polynom c a]
build checked add@(a:as) = build (checked ++ [a]) (as ++ (checkOne a checked add))
build checked [] = checked

makeGroebner :: (Eq c, Fractional c, Num a, Ord a) =>
                [Polynom c a] -> [Polynom c a]
makeGroebner (b:bs) = build [b] bs
    where build checked add@(a:as) = build (checked ++ [a]) (as ++ (checkOne a checked add))
          build checked [] = checked

test1 = [
    P [M 1 [2,0], M (-2) [1,0], M 1 [0,2], M (-26) [0,1], M 70 [0,0]] :: Polynom Double Int,
    P [M 1 [2,0], M (-22) [1,0], M 1 [0,2], M (-16) [0,1], M 160 [0,0]] :: Polynom Double Int,
    P [M 1 [2,0], M (-20) [1,0], M 1 [0,2], M (-2) [0,1], M 76 [0,0]] :: Polynom Double Int
    ]

test2 = [
    P [M 1 [2,0,0], M (-1) [0,0,0]] :: Polynom Double Int,
    P [M 1 [1,1,0], M (-1) [0,1,0]] :: Polynom Double Int,
    P [M 1 [1,0,1], M (1) [0,0,1]] :: Polynom Double Int

    ]
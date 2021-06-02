
--Lesson 20-21
import Data.Monoid

{- a
long
comment -}

mult2 :: Integer -> Integer
mult2 a = a * 2

ccc :: Char -> Char
ccc x = 'a'

fldr :: (a -> b -> b) -> b -> [a] -> b
fldr f acc [] = acc
fldr f acc (x:xs) = f x (fldr f acc xs)

fldl :: (b -> a -> b) -> b -> [a] -> b
fldl f acc [] = acc
fldl f acc (x:xs) = fldl f (f acc x) xs


binding :: IO ()
binding = do
    putStr "Enter your name please: "
    name <- getLine
    putStrLn ((++) "Hello, " name)


sum' :: (Foldable t, Num a) => t a -> a
sum' x = getSum (foldMap Sum x)


eq :: Eq a => a -> (a -> Bool)
eq a = (==) a


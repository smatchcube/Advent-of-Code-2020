import           Data.List
import           Data.List.Split

main :: IO ()
main = do
  listOfNumbers <- map read . init . splitOn "\n" <$> readFile "input"
  let n1 = silver listOfNumbers
      n2 = gold listOfNumbers n1 in do
    putStrLn $ "Part one: " ++ show n1
    putStrLn $ "Part two: " ++ show n2

-- | Find if two distinct integers of a list
--   sum to a specific integer
isNotSumOfTwo :: Integer -> [Integer] -> Bool
isNotSumOfTwo n ns =
  null [ x | x <- ns, (n - x) `elem` delete x ns]

silver :: [Integer] -> Integer
silver ns =
   case find (uncurry isNotSumOfTwo) (zip (drop 25 ns) nss) of
     Just (n, _) -> n
     Nothing     -> error "No solution for part one!"
  where nss = go $ cycle ns
        go ns = take 25 ns : go (tail ns)

gold :: [Integer] -> Integer -> Integer
gold ns n =
  case find (\ns -> sum ns == n) nss of
    Just ms -> minimum ms + maximum ms
    Nothing -> error "No solution for part two!"
  where nss = concatMap (\i -> divvy i 1 ns) [2..length ns]



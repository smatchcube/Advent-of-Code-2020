import           Data.List

main :: IO ()
main = do
  ns <- map read . lines <$> readFile "input"
  putStrLn $ "Part one: " ++ show (silver ns)

silver :: [Integer] -> Integer
silver js = oneJoltDiff * threeJoltsDiff
  where (_, oneJoltDiff, threeJoltsDiff) =
          foldl go (0, 0, 1) $ sort js
        go (currentJolt, oneDiffCount, threeDiffCount) j =
          case j - currentJolt of
            1 -> (j, oneDiffCount + 1, threeDiffCount)
            3 -> (j, oneDiffCount, threeDiffCount + 1)
            _ -> (j, oneDiffCount, threeDiffCount)

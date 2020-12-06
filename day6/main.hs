import           Data.List       (intersect, nub)
import           Data.List.Split (splitOn)

main :: IO ()
main = do
  groupsOfAnswers <- splitOn "\n\n" <$> readFile "input"
  putStrLn $ "Part one: " ++
    show (sum $ map (length . nub . filter (/= '\n')) groupsOfAnswers)
  putStrLn $ "Part two: " ++
    show (sum $ map (length . (foldr intersect ['a'..'z']) . lines) groupsOfAnswers)

{- Need to refactor this solution and solve part two. -}

import qualified Data.HashMap.Strict as HM
import           Data.List.Split     (splitOn)
import qualified Data.Set            as Set

type Color = String
type Rule = (Color, HM.HashMap Color Int)
type RuleMap = HM.HashMap Color (HM.HashMap Color Int)

parseRule :: String -> Rule
parseRule str = (color, allowedColors)
  where [color, rest] = splitOn " bags contain " str
        allowedColors =
          case rest of
            "no other bags." -> HM.empty
            _ ->  HM.fromList $ map ((\xs -> (xs !! 1 ++ " " ++ xs !! 2,  read (xs !! 0))) . words)
                              $ splitOn "," rest

solve :: RuleMap -> Color -> Int
solve ruleMap color = go (Set.singleton color) Set.empty
  where go toCheck contain =
          if Set.null toCheck then Set.size contain
          else let (el:toCheckk) = Set.elems toCheck in
            go (Set.union (Set.fromList toCheckk) (Set.fromList (HM.keys (HM.filter (HM.member el) ruleMap))))
               (Set.union contain (Set.fromList (HM.keys (HM.filter (HM.member el) ruleMap))))



main = do
  ruleMap <- HM.fromList . map parseRule . lines <$> readFile "input"
  print $ solve ruleMap "shiny gold"

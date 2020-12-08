import           Data.Array
import           Data.Either (fromLeft, fromRight, rights)
import qualified Data.Set    as Set

data Instruction = ACC Int | JMP Int | NOP Int

data State = State { programCounter :: Int
                   , accumulator    :: Int }

main :: IO ()
main = do
  program <- readProgram <$> readFile "input"
  putStrLn $ "Part one: " ++ show (fromLeft 0 $ run program)
  putStrLn $ "Part two: " ++ show (head $ rights $ map run $ modifiedPrograms program)

-- | Build the program from the source code
readProgram :: String -> Array Int Instruction
readProgram s = listArray bounds instructionList
  where instructionList = map readInstruction $ lines s
        bounds = (0, length instructionList - 1)
        readInstruction s = case splitAt 5 s of
                              ("acc -", n) -> ACC $ negate $ read n
                              ("acc +", n) -> ACC $ read n
                              ("jmp -", n) -> JMP $ negate $ read n
                              ("jmp +", n) -> JMP $ read n
                              ("nop -", n) -> NOP $ negate $ read n
                              ("nop +", n) -> NOP $ read n

-- | Build the list of candidates for the correct program
modifiedPrograms :: Array Int Instruction -> [Array Int Instruction]
modifiedPrograms arr =
  [ arr // [(i, flipInstruction (arr ! i))] | i <- indices arr, isNotAcc (arr ! i)]
  where flipInstruction x =
          case x of
            ACC n -> ACC n
            JMP n -> NOP n
            NOP n -> JMP n
        isNotAcc (ACC _) = False
        isNotAcc _       = True

-- | Advance in the program according to the current state
-- Return the next state
step :: State -> Array Int Instruction -> State
step (State pc acc) arr =
  case arr ! pc of
    ACC n -> State (succ pc) (acc + n)
    JMP n -> State (pc + n) acc
    NOP _ -> State (succ pc) acc

-- | Runs the program given an array of instructions
-- The returned value is the last state of the accumulator:
--       - wrappded in a Left if the program would enter in a loop
--       - wrappded in a Right if the program ends normally
run :: Array Int Instruction -> Either Int Int
run arr = go (State 0 0) Set.empty
  where go state@(State pc acc) visitedPC
          | pc == snd (bounds arr) + 1 = Right acc --program finished
          | programCounter nextState `Set.member` visitedPC = Left acc --loop entered
          | otherwise = go nextState $ Set.insert pc visitedPC
          where nextState = step state arr
                nextPC = programCounter nextState

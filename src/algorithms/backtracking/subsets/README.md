# Subsets (Power Set)

## Description

**Subsets** (also called the power set problem) generates all possible subsets of a given set of distinct integers using **backtracking**.

At each recursive call, the current subset is recorded. The algorithm then iterates over the remaining elements, choosing one, recursing deeper, and undoing the choice - the classic **choose / explore / undo** pattern.

---

## How It Works

1. Record the current subset into the result.
2. Iterate over elements starting from `index` to avoid duplicates.
3. **Choose**: append `nums[i]` to the current subset.
4. **Explore**: recurse with `i + 1` as the new start index.
5. **Undo**: pop the last element to restore state before the next iteration.

---

## Example

Input: `[1, 2, 3]`

```
backtrack(index=0, subset=[])     -> record []
  choose 1 -> backtrack(index=1, subset=[1])   -> record [1]
    choose 2 -> backtrack(index=2, subset=[1,2]) -> record [1,2]
      choose 3 -> backtrack(index=3, subset=[1,2,3]) -> record [1,2,3]
    choose 3 -> backtrack(index=3, subset=[1,3]) -> record [1,3]
  choose 2 -> backtrack(index=2, subset=[2])   -> record [2]
    choose 3 -> backtrack(index=3, subset=[2,3]) -> record [2,3]
  choose 3 -> backtrack(index=3, subset=[3])   -> record [3]
```

Output (8 subsets = 2^3):
```
[ ]
[ 1 ]
[ 1 2 ]
[ 1 2 3 ]
[ 1 3 ]
[ 2 ]
[ 2 3 ]
[ 3 ]
```

---

## Complexity

| | Complexity |
|---|---|
| Time | O(n * 2^n) - 2^n subsets, each copied in O(n) |
| Space | O(n) - recursion depth and the current subset buffer |

---

## Key Properties

- **No duplicates**: advancing the start index to `i + 1` ensures each element is used at most once per subset and each subset appears exactly once.
- **All sizes covered**: subsets of every size from 0 to n are produced naturally without extra logic.
- **In-place state**: a single `subset` vector is mutated and restored, avoiding per-call allocations.

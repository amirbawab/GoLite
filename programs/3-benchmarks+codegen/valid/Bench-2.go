//~69836
package main

var search_depth int = 10
var size_x int = 8
var size_y int = 8

type PuzzleState struct {
	numbers     []int
	numbers_len int
	cost        int
}

type XYPos struct {
	x int
	y int
}

type PossibleMoves struct {
	moves []PuzzleState
	size  int
}

type StateNode struct {
	data          PuzzleState
	children      []StateNode
	size_children int
}

func _compute_inline_pos_from_xy(pos XYPos) int {
	return pos.x + pos.y*size_x
}

func _compute_xy_pos_from_inline(idx int) XYPos {
	var pos XYPos
	pos.x = idx % size_x
	if idx < size_x {
		pos.y = 0
	} else {
		pos.y = idx / size_x
	}

	return pos
}

func _index_of(arr []int, len int, val int) int {
	for i := 0; i < len; i++ {
		if arr[i] == val {
			return i
		}
	}
	return -1
}

func puzzle_get_possible_moves(puzzle PuzzleState) PossibleMoves {
	var result PossibleMoves
	result.size = 0

	var target_idx int = _index_of(puzzle.numbers, puzzle.numbers_len, 0) //finds the 0 location within array
	var target_pos XYPos = _compute_xy_pos_from_inline(target_idx)
	var new_pos XYPos

	// move across y
	if (target_pos.y-1) >= 0 && (target_pos.y+1) < size_y {
		// y - 1 swap
		var move_1 PuzzleState = puzzle
		new_pos = target_pos
		new_pos.y = new_pos.y - 1
		move_1.numbers[_compute_inline_pos_from_xy(new_pos)],
			move_1.numbers[_compute_inline_pos_from_xy(target_pos)] =
			move_1.numbers[_compute_inline_pos_from_xy(target_pos)],
			move_1.numbers[_compute_inline_pos_from_xy(new_pos)]
		move_1.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

		// y + 1 swap
		var move_2 PuzzleState = puzzle
		new_pos = target_pos
		new_pos.y = new_pos.y + 1
		move_2.numbers[_compute_inline_pos_from_xy(new_pos)],
			move_2.numbers[_compute_inline_pos_from_xy(target_pos)] =
			move_2.numbers[_compute_inline_pos_from_xy(target_pos)],
			move_2.numbers[_compute_inline_pos_from_xy(new_pos)]
		move_2.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

		result.moves = append(result.moves, move_1)
		result.size++
		result.moves = append(result.moves, move_2)
		result.size++
	} else {
		if target_pos.y-1 >= 0 { // only y - 1 is possible
			// y - 1 swap
			var move PuzzleState = puzzle
			new_pos = target_pos
			new_pos.y = new_pos.y - 1
			move.numbers[_compute_inline_pos_from_xy(new_pos)],
				move.numbers[_compute_inline_pos_from_xy(target_pos)] =
				move.numbers[_compute_inline_pos_from_xy(target_pos)],
				move.numbers[_compute_inline_pos_from_xy(new_pos)]
			move.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

			result.moves = append(result.moves, move)
			result.size++
		} else { // only y + 1 is possible
			// y + 1 swap
			var move PuzzleState = puzzle
			new_pos = target_pos
			new_pos.y = new_pos.y + 1
			move.numbers[_compute_inline_pos_from_xy(new_pos)],
				move.numbers[_compute_inline_pos_from_xy(target_pos)] =
				move.numbers[_compute_inline_pos_from_xy(target_pos)],
				move.numbers[_compute_inline_pos_from_xy(new_pos)]
			move.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

			result.moves = append(result.moves, move)
			result.size++
		}
	}

	// move across x
	if (target_pos.x-1) >= 0 && (target_pos.x+1) < size_x {
		// x - 1 swap
		var move_1 PuzzleState = puzzle
		new_pos = target_pos
		new_pos.x = new_pos.x - 1
		move_1.numbers[_compute_inline_pos_from_xy(new_pos)],
			move_1.numbers[_compute_inline_pos_from_xy(target_pos)] =
			move_1.numbers[_compute_inline_pos_from_xy(target_pos)],
			move_1.numbers[_compute_inline_pos_from_xy(new_pos)]
		move_1.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

		// x + 1 swap
		var move_2 PuzzleState = puzzle
		new_pos = target_pos
		new_pos.x = new_pos.x + 1
		move_2.numbers[_compute_inline_pos_from_xy(new_pos)],
			move_2.numbers[_compute_inline_pos_from_xy(target_pos)] =
			move_2.numbers[_compute_inline_pos_from_xy(target_pos)],
			move_2.numbers[_compute_inline_pos_from_xy(new_pos)]
		move_2.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

		result.moves = append(result.moves, move_1)
		result.size++
		result.moves = append(result.moves, move_2)
		result.size++
	} else {
		if target_pos.x-1 >= 0 { // only x - 1 is possible
			// x - 1 swap
			var move PuzzleState = puzzle
			new_pos = target_pos
			new_pos.x = new_pos.x - 1
			move.numbers[_compute_inline_pos_from_xy(new_pos)],
				move.numbers[_compute_inline_pos_from_xy(target_pos)] =
				move.numbers[_compute_inline_pos_from_xy(target_pos)],
				move.numbers[_compute_inline_pos_from_xy(new_pos)]
			move.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

			result.moves = append(result.moves, move)
			result.size++
		} else { // only x + 1 is possible
			// x + 1 swap
			var move PuzzleState = puzzle
			new_pos = target_pos
			new_pos.x = new_pos.x + 1
			move.numbers[_compute_inline_pos_from_xy(new_pos)],
				move.numbers[_compute_inline_pos_from_xy(target_pos)] =
				move.numbers[_compute_inline_pos_from_xy(target_pos)],
				move.numbers[_compute_inline_pos_from_xy(new_pos)]
			move.cost = puzzle.numbers[_compute_inline_pos_from_xy(new_pos)]

			result.moves = append(result.moves, move)
			result.size++
		}
	}

	return result
}

func puzzle_state_to_node(state PuzzleState) StateNode {
	var result StateNode
	result.data = state
	result.size_children = 0
	return result
}

func possible_moves_to_graph(moves PossibleMoves) []StateNode {
	var nodes []StateNode
	for i := 0; i < moves.size; i++ {
		var new_node StateNode = puzzle_state_to_node(moves.moves[i])
		nodes = append(nodes, new_node)
	}

	return nodes
}

func initialize_puzzle(numbers []int) PuzzleState {
	var puzzle PuzzleState
	puzzle.numbers = numbers
	puzzle.numbers_len = size_x * size_y

	return puzzle
}

var num_search_space_state int = 0

func construct_search_space(root StateNode, level_rem int) StateNode {
	if level_rem <= 0 {
		var leaf_node StateNode
		return leaf_node
	}

	var moves PossibleMoves = puzzle_get_possible_moves(root.data)
	num_search_space_state++
	for i := 0; i < moves.size; i++ {
		var child PuzzleState = moves.moves[i]
		var child_node StateNode = puzzle_state_to_node(child)
		root.children = append(root.children, construct_search_space(child_node, level_rem-1))
	}

	return root
}

func main() {
	//[ 5, 1, 4, 2, 3, 6
	//  1, 2, 3, 4, 4, 4
	//  7, 6, 0, 3, 3, 3
	//  9, 9, 9, 9, 9, 9
	//	4, 3, 2, 7, ]
	var numbers []int
	numbers = append(numbers, 5)
	numbers = append(numbers, 1)
	numbers = append(numbers, 4)
	numbers = append(numbers, 2)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 1)
	numbers = append(numbers, 2)
	numbers = append(numbers, 3)
	numbers = append(numbers, 4)
	numbers = append(numbers, 4)
	numbers = append(numbers, 4)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 5)
	numbers = append(numbers, 7)
	numbers = append(numbers, 6)
	numbers = append(numbers, 0)
	numbers = append(numbers, 3)
	numbers = append(numbers, 3)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 2)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 10)
	numbers = append(numbers, 4)
	numbers = append(numbers, 3)
	numbers = append(numbers, 2)
	numbers = append(numbers, 7)
	numbers = append(numbers, 8)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 5)
	numbers = append(numbers, 7)
	numbers = append(numbers, 6)
	numbers = append(numbers, 0)
	numbers = append(numbers, 3)
	numbers = append(numbers, 3)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 2)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 9)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	numbers = append(numbers, 10)
	numbers = append(numbers, 4)
	numbers = append(numbers, 3)
	numbers = append(numbers, 2)
	numbers = append(numbers, 7)
	numbers = append(numbers, 8)
	numbers = append(numbers, 3)
	numbers = append(numbers, 6)

	var puzzle PuzzleState = initialize_puzzle(numbers)
	var root_node StateNode = puzzle_state_to_node(puzzle)
	root_node = construct_search_space(root_node, search_depth)

	println(num_search_space_state) // test232
}

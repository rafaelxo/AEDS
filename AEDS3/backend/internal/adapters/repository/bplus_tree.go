package repository

const bPlusMaxKeys = 15

type bPlusNode struct {
	leaf     bool
	keys     []int64
	values   [][]int64
	children []*bPlusNode
	next     *bPlusNode
}

type bPlusTree struct {
	root  *bPlusNode
	first *bPlusNode
}

func newBPlusTree() *bPlusTree {
	return &bPlusTree{}
}

func (t *bPlusTree) Reset() {
	t.root = nil
	t.first = nil
}

func (t *bPlusTree) Insert(key int64, value int64) {
	if t.root == nil {
		leaf := &bPlusNode{leaf: true, keys: []int64{key}, values: [][]int64{{value}}}
		t.root = leaf
		t.first = leaf
		return
	}

	promoted, right, split := t.insert(t.root, key, value)
	if !split {
		return
	}
	t.root = &bPlusNode{
		keys:     []int64{promoted},
		children: []*bPlusNode{t.root, right},
	}
}

func (t *bPlusTree) insert(node *bPlusNode, key int64, value int64) (int64, *bPlusNode, bool) {
	if node.leaf {
		pos := lowerBoundInt64(node.keys, key)
		if pos < len(node.keys) && node.keys[pos] == key {
			for _, current := range node.values[pos] {
				if current == value {
					return 0, nil, false
				}
			}
			node.values[pos] = append(node.values[pos], value)
			return 0, nil, false
		}
		node.keys = insertInt64At(node.keys, pos, key)
		node.values = insertInt64SliceAt(node.values, pos, []int64{value})
		if len(node.keys) <= bPlusMaxKeys {
			return 0, nil, false
		}
		return splitLeaf(node)
	}

	childIndex := upperBoundInt64(node.keys, key)
	promoted, right, split := t.insert(node.children[childIndex], key, value)
	if !split {
		return 0, nil, false
	}
	node.keys = insertInt64At(node.keys, childIndex, promoted)
	node.children = insertNodeAt(node.children, childIndex+1, right)
	if len(node.keys) <= bPlusMaxKeys {
		return 0, nil, false
	}
	return splitInternal(node)
}

func (t *bPlusTree) Delete(key int64, value int64) {
	if t.root == nil {
		return
	}
	leaf := t.findLeaf(key)
	if leaf == nil {
		return
	}
	pos := lowerBoundInt64(leaf.keys, key)
	if pos >= len(leaf.keys) || leaf.keys[pos] != key {
		return
	}
	values := leaf.values[pos]
	filtered := values[:0]
	for _, current := range values {
		if current != value {
			filtered = append(filtered, current)
		}
	}
	if len(filtered) > 0 {
		leaf.values[pos] = filtered
		return
	}
	leaf.keys = append(leaf.keys[:pos], leaf.keys[pos+1:]...)
	leaf.values = append(leaf.values[:pos], leaf.values[pos+1:]...)
}

func (t *bPlusTree) Range(minKey, maxKey int64) []int64 {
	if t.first == nil {
		return []int64{}
	}
	values := make([]int64, 0)
	for leaf := t.first; leaf != nil; leaf = leaf.next {
		for i, key := range leaf.keys {
			if key < minKey {
				continue
			}
			if key > maxKey {
				return values
			}
			values = append(values, leaf.values[i]...)
		}
	}
	return values
}

func (t *bPlusTree) findLeaf(key int64) *bPlusNode {
	node := t.root
	for node != nil && !node.leaf {
		node = node.children[upperBoundInt64(node.keys, key)]
	}
	return node
}

func splitLeaf(node *bPlusNode) (int64, *bPlusNode, bool) {
	mid := len(node.keys) / 2
	right := &bPlusNode{
		leaf:   true,
		keys:   append([]int64(nil), node.keys[mid:]...),
		values: append([][]int64(nil), node.values[mid:]...),
		next:   node.next,
	}
	node.keys = node.keys[:mid]
	node.values = node.values[:mid]
	node.next = right
	return right.keys[0], right, true
}

func splitInternal(node *bPlusNode) (int64, *bPlusNode, bool) {
	mid := len(node.keys) / 2
	promoted := node.keys[mid]
	right := &bPlusNode{
		keys:     append([]int64(nil), node.keys[mid+1:]...),
		children: append([]*bPlusNode(nil), node.children[mid+1:]...),
	}
	node.keys = node.keys[:mid]
	node.children = node.children[:mid+1]
	return promoted, right, true
}

func lowerBoundInt64(values []int64, key int64) int {
	lo, hi := 0, len(values)
	for lo < hi {
		mid := (lo + hi) / 2
		if values[mid] < key {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

func upperBoundInt64(values []int64, key int64) int {
	lo, hi := 0, len(values)
	for lo < hi {
		mid := (lo + hi) / 2
		if values[mid] <= key {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

func insertInt64At(values []int64, index int, value int64) []int64 {
	values = append(values, 0)
	copy(values[index+1:], values[index:])
	values[index] = value
	return values
}

func insertInt64SliceAt(values [][]int64, index int, value []int64) [][]int64 {
	values = append(values, nil)
	copy(values[index+1:], values[index:])
	values[index] = value
	return values
}

func insertNodeAt(values []*bPlusNode, index int, value *bPlusNode) []*bPlusNode {
	values = append(values, nil)
	copy(values[index+1:], values[index:])
	values[index] = value
	return values
}

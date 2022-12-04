package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

/**
Lowercase item types a through z have priorities 1 through 26.
Uppercase item types A through Z have priorities 27 through 52.
**/

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func samesies(a, b []string) string {
	mb := make(map[string]struct{}, len(b))
	for _, x := range b {
		mb[x] = struct{}{}
	}
	for _, x := range a {
		if _, found := mb[x]; found {
			return x
		}
	}
	panic("Biatch") // NEVER
}

func valueFunc(i string) int {
	k := []string{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}
	for p, v := range k {
		if v == strings.ToLower(i) {
			offset := 0
			if strings.ToUpper(i) == i {
				offset = 26
			}
			return p + offset + 1
		}
	}
	return -1
}

func prob1(fileScanner *bufio.Scanner) int {
	res := 0
	for fileScanner.Scan() {
		line := strings.Split(fileScanner.Text(), "")
		mid := len(line) / 2
		firstCom := line[:mid]
		secondCom := line[mid:]

		diff := samesies(firstCom, secondCom)

		res += valueFunc(diff)

	}
	return res
}

func intersection(s1, s2 []string) (inter []string) {
	hash := make(map[string]bool)
	for _, e := range s1 {
		hash[e] = true
	}
	for _, e := range s2 {
		// If elements present in the hashmap then append intersection list.
		if hash[e] {
			inter = append(inter, e)
		}
	}
	//Remove dups from slice.
	inter = removeDups(inter)
	return
}

//Remove dups from slice.
func removeDups(elements []string) (nodups []string) {
	encountered := make(map[string]bool)
	for _, element := range elements {
		if !encountered[element] {
			nodups = append(nodups, element)
			encountered[element] = true
		}
	}
	return
}

func prob2(fileScanner *bufio.Scanner) int {
	badgeSum := 0
	i := 0
	lines := [][]string{}
	for fileScanner.Scan() {
		if i == 2 {
			line := strings.Split(fileScanner.Text(), "")
			lines = append(lines, line)
			// get commone between 3 slices
			common := intersection(intersection(lines[0], lines[1]), lines[2])
			if len(common) == 0 {
				panic("Error")
			}
			badgeSum += valueFunc(common[0])
			// reset
			i = 0
			lines = [][]string{}

		} else {
			line := strings.Split(fileScanner.Text(), "")
			lines = append(lines, line)
			i++
		}
	}

	return badgeSum
}

func main() {
	filename := "./input.txt"
	f, err := os.Open(filename)
	check(err)

	fileScanner := bufio.NewScanner(f)

	fileScanner.Split(bufio.ScanLines)

	fmt.Println(prob2(fileScanner))
	f.Close()

}

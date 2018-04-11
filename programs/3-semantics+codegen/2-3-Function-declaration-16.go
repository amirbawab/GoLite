package main

func hello() int {
    switch true {
    case 1:
        return 1
    } // missing return in default
}

(define TREE '(1 (2 (3 4)) 6 (7 8 9)))
(define MYTREE '(1 2 (3) (4 5 6 (7 8) (9))) )

(define map-tree
  (lambda (f tree)
    (cond ((null? tree) '())
          ((pair? tree) (cons (map-tree f (car tree)) (map-tree f (cdr tree))))
          (else (f tree))
    )
  )
)

(define map-tree2
  (lambda (f tree)
    (if (pair? tree)
        (map (lambda (t) (map-tree2 f t)) tree)
        (f tree)
    )
  )
)

(map-tree even? TREE)
(map-tree (lambda (x) (* x x)) TREE)
(map-tree even? MYTREE)
(map-tree (lambda (x) (+ x 1)) MYTREE)
(map-tree2 even? TREE)
(map-tree2 (lambda (x) (* x x)) TREE)
(map-tree2 even? MYTREE)
(map-tree2 (lambda (x) (> x 4)) MYTREE)
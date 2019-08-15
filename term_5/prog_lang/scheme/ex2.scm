(define kakeizu
  (read
     (open-input-file "/usr/local/class/scheme/kakeizu")))

(define get-depth
  (lambda (tree d)
    (if (> d 0) (apply append (map (lambda (t) (get-depth t (- d 1))) (cdr tree)))
                (map car (list tree))
    )
  )
)

(define search
  (lambda (tree name depth)
    (cond ((equal? name (car tree)) depth)
          ((null? (cdr tree)) 0)
          (else (apply + (map (lambda(t) (search t name (+ depth 1))) (cdr tree))))
    )
  )
)

(define get-cousin
  (lambda (tree name)
    (get-depth tree (search tree name 0))
  )
 )

(define get-path
  (lambda (tree name)
    (cond
      ((equal? name (car tree)) (list name))
      ((= (search tree name 0) 0) '())
      (else (cons (car tree) (apply append (map (lambda (t) (get-path t name)) (cdr tree)))))
    )
  )
)

(get-depth kakeizu 1)
(get-depth kakeizu 3)
(get-depth kakeizu 6)
(search kakeizu '治察 0)
(get-cousin kakeizu '秀忠)
(get-cousin kakeizu '吉宗)
(get-cousin kakeizu '家継)
(get-path kakeizu '家康)
(get-path kakeizu '定信)
(get-path kakeizu '昌丸)

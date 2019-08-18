(define kakeizu
  (read
     (open-input-file "./kakeizu")))

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
    (let ((cartr (car tree)))
      (cond
        ((equal? name cartr) (list name))
        ((= (search tree name 0) 0) '())
        (else (cons cartr (apply append (map (lambda (t) (get-path t name)) (cdr tree)))))
    ))
  )
)

(get-depth kakeizu 1)
(get-depth kakeizu 0)
(get-depth kakeizu 6)
(get-depth kakeizu 4)
(search kakeizu '治察 0)
(get-cousin kakeizu '秀忠)
(get-cousin kakeizu '吉宗)
(get-cousin kakeizu '家継)
(get-cousin kakeizu '斎匡)
(get-path kakeizu '家光)
(get-path kakeizu '義直)
(get-path kakeizu '家定)
(defun compare (x y)
	(if (> (+ x 10) (* y 2)) 
		t
		nil
	)
)

(defun power-of-two (n)
	(if (= n 0)
		1
		(* 2 (power-of-two (- n 1)))
	)
)

(defun num-even (alist)
	(let ((result 0))
		(dolist (element alist result)
			(when (= (MOD element 2) 0) (setf result (+ result 1)))
		)
	)

)

(defun listofprimes (l)
	(setf size (length l))
	(dolist(i size l)
		(if not (primep (i))
			nil
			t
		)
	)
)

(defun shorter (l1 l2)
	(cond 
		((= (length l1) (length l2)) l1)
		((> (length l1) (length l2)) l2)
		((> (length l2) (length l1)) l1)
	)
)


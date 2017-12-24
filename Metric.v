Require Import QArith.

Open Scope Q_scope.

Definition RPlus := forall R, R > 0.
  
Inductive QInfty :=
  | q : Q -> QInfty
  | infty : QInfty.
                    
Definition QInftyPlus (x y : QInfty) :=
  match x, y with
  | q x', q y' => q (x' + y')
  | infty, _ => infty
  | _, infty => infty
  end.
                    
Definition QInftyLe (x y : QInfty) :=
  match x, y with
  | q x', q y' => x' <= y'
  | _, infty => True
  | _, _ => False
  end.
                    
Definition QInftyEq (x y : QInfty) :=
  match x, y with
  | q x', q y' => x' == y'
  | _, _ => False
  end.

Infix "+" := QInftyPlus : QInfty_scope.
Infix "<=" := QInftyLe : QInfty_scope.
Infix "==" := QInftyEq : QInfty_scope.

Open Scope QInfty_scope.

Record extended_quasimetric_space :=
  { base : Type;
    d :  base -> base -> QInfty;
    base_eq :  base -> base -> Prop;
    indisc : forall (x y : base), d x y == q 0 <-> base_eq x y;
    tri : forall (x y z : base), d x z <= d x z + d y z;
    }.

Definition qdist (x : Q) (y : Q) :=
  if Qle_bool (x : Q) (y : Q)
  then q (y - x)
  else infty.

Theorem q_eq_plus_minus : forall (x y z : Q), (x + y == z)%Q <-> (x == z - y)%Q.
Proof.
  intros.

  split.
  intros.
  Search "Q" "plus".
  rewrite <- (Qplus_inj_r (x + y) (z) (-y)) in H.
  symmetry.
  unfold Qminus.
  
  rewrite (Qeq_trans (z + - y) (x + y + - y) x).
  apply Qeq_refl.
  
  
   rewrite (Qeq_trans (x + y + - y) (z + - y) x).
  . 

  

Theorem q_monotonous : forall (x y : Q), q x == q y <-> (x == y)%Q.
Proof.
  intros.
  
  split.
  intros.
  auto.

  intros.
  auto.
Qed.

Theorem qdist_indisc : forall (x y : Q), qdist x y == q 0 <-> (x == y)%Q.
Proof.
  intros.
  unfold qdist.
  
  destruct Qle_bool eqn:?.
  symmetry.
  split.
  intros.
  subst.
  simpl.
  unfold Qminus.
  Search "Q" "plus".
  rewrite <- Qplus_inj_r in H.
  Unshelve.
  Focus 4.
  apply (-x).
  Search "Q" "opp".
  pose proof Qplus_opp_r as H1.
  specialize (H1 x).
  symmetry in H.
  Search "Q" "trans".
  apply  (Qeq_trans (y + - x) (x + - x) 0).
  
  assumption.
  assumption.

  intros.
  rewrite Qle_bool_iff in Heqb.
  rewrite q_monotonous in H.
  rewrite <- q_le_unwrap in Heqb.
  rewrite <- q_eq_unwrap in H.
    
  rewrite Qplus_opp_r in H.


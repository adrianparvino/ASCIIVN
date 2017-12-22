Require Import QArith Qcanon.

Open Scope Q_scope.

Definition RPlus := forall R, R > 0.
  
Inductive QcInfty :=
  | q : Qc -> QcInfty
  | infty : QcInfty.
                    
Definition QcInftyPlus (x y : QcInfty) :=
  match x, y with
  | q x', q y' => q (x' + y')
  | infty, _ => infty
  | _, infty => infty
  end.
                    
Definition QcInftyLe (x y : QcInfty) :=
  match x, y with
  | q x', q y' => x' <= y'
  | _, infty => True
  | _, _ => False
  end.

Infix "+" := QcInftyPlus : QcInfty_scope.
Infix "<=" := QcInftyLe : QcInfty_scope.

Open Scope QcInfty_scope.

Record extended_quasimetric_space :=
  { base : Type;
    d :  base -> base -> QcInfty;
    indisc : forall (x y : base), d x y = q 0 <-> x = y;
    tri : forall (x y z : base), d x z <= d x z + d y z;
    }.

Definition qdist (x : Qc) (y : Qc) :=
  if Qle_bool (x : Q) (y : Q)
  then q (y - x)
  else infty.

Lemma q_eq_unwrap : forall (x y : Qc), x = y <-> q x = q y.
Proof.
  intros.
  
  split.
  intro.
  subst.
  reflexivity.
  
  injection 1.
  tauto.
Qed.
  
Lemma q_le_unwrap : forall (x y : Qc), (x <= y)%Qc <-> q x <= q y.
Proof.
  intros.
  
  split.
  intro.
  auto.

  auto.
Qed.

Lemma qc_eq_plus : forall (x y z : Qc), (x - y)%Qc = z <-> x = (z + y)%Qc.
Proof.
  intros.
  
  split.
  intro.
  Search "Q" "plus".
  Search "Q" "eq" "if".
  rewrite Qcplus_inj_r in H.
  

  
Lemma q_monotonous : forall (x y : Qc), Qle x y <-> q x <= q y.
Proof.
  intros.

  split.
  auto.

  auto.
Qed.
  
Theorem qdist_indisc : forall (x y : Qc), qdist x y = q 0 <-> x = y.
Proof.
  intros.
  unfold qdist.
  destruct Qle_bool eqn:?.
  symmetry.
  split.
  intros.
  subst.
  simpl.
  unfold Qcminus.
  Search "Qc" "plus".
  rewrite Qcplus_opp_r.
  reflexivity.

  intros.
  rewrite Qle_bool_iff in Heqb.
  rewrite q_monotonous in Heqb.
  rewrite <- q_le_unwrap in Heqb.
  rewrite <- q_eq_unwrap in H.
    
  rewrite Qcplus_opp_r in H.


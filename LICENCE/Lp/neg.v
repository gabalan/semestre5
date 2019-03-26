Section Peirce_double_neg.
  Variables P Q S: Prop.

  (* Executez cette preuve en essayant de comprendre le sens de chacune des nouvelles tactiques utilisées. *)
  Lemma absurde_exemple: P -> ~P -> S.
    intros p np.
    unfold not in np.
    assert(F: False).
    apply np; assumption.
    destruct F.
  Qed.
  
    (* Réalisez les preuves suivantes. *)
  Lemma absurde: (P -> Q) -> (P -> ~Q) -> (P -> S).
    intros.
    assert(F:False).
    apply H0.
    assumption.
    apply H.
    assumption.
    destruct F.
  Qed.

  Lemma triple_abs: ~P -> ~~~P.
  intro H.
  intro H0.
  apply H0.
  assumption.
  Qed. 
  
  Lemma equiv1 : (~P -> P) <-> ~~P.
    split.
    intro H.
    intro H0.
    assert(F:False).
    apply H0.
    apply H.
    assumption.
    destruct F.
    intro H.
    intro H0.
    unfold not in H0.
    unfold not in H.
    assert(F:False).
    apply H.
    apply H0.
    destruct F.
  Qed.


End Peirce_double_neg.


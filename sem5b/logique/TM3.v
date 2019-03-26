(* Logique du premier ordre *)

(** Tactiques :
  pour forall :  
    introduction : 
            intro, intros.
    elimination :
            apply, eapply, specialize.
            (H x ...)

  pour exists : 
     introduction: exists (fournir le terme)
     elimintation: destruct.

  pour = reflexivity (introduction),
         rewrite H   [in HØ] (elimination)
         rewrite <- H [in H0]
                  
 *)

(* tactique maison pour eliminer un forall *)
(* il faut fournir le terme temoin *)

Ltac forall_e H t := (generalize (H t); intro).

(* Exemple *)

Example E0 : ~(forall x:nat, x <> x).
Proof.
  intro H.                                       
  forall_e H 42.
  apply H0.
  trivial. (* reflexivity. *)
Qed.

Section Syllogismes. (* Entrainements *)
  Variable Etre: Type.
  Variables humain mortel animal : Etre -> Prop.

  Variable Socrate : Etre.
  Variable Rhino : Etre.

  Hypothesis HM : forall x,  humain x -> mortel x.
  Hypothesis HSocrate : humain Socrate.
  Hypothesis Etre_disj : forall x:Etre,  humain x \/ animal x.
  Hypothesis Hrhino : ~ humain Rhino.

  Lemma Syllogisme :  mortel Socrate.
  Proof.
    apply HM. (* elimination du forall et modus-ponens *)
    assumption.
  Qed.

  Lemma contraposee : forall x, ~ mortel x -> ~ humain x.
  Proof.  
    intros x Hx H .
    apply Hx.
    apply HM; assumption.
  Qed.    

  Lemma Lm: exists x, mortel x.
  Proof.  
   exists Socrate.  (* introduction de l'existentiel *)
   apply Syllogisme.  
  Qed.


  Lemma La: exists x, animal x.
  Proof.  
    exists Rhino.
    destruct (Etre_disj Rhino).  
    - contradiction.
    - assumption.
  Qed.

  Lemma L : ~(exists x:Etre,  ~ humain x /\ ~ animal x).
  Proof.
    intro H.
    destruct H as [e He]. (* elimination de l'existentiel *)
    destruct He.
    forall_e Etre_disj e.
    destruct H1.
    contradiction.
    contradiction.
  Qed.

End Syllogismes.

Section Egalite. (* Entrainements, sur l'egalite *) 
  Variable A : Type.
  Variable f : A -> A.

  Lemma E1 : forall x:A, exists y: A, x=y.
  Proof.
   intros x.
   exists x.
   reflexivity. 
   Qed.

  Lemma E2 : forall x y z: A, x = y -> y = z -> x = z.
  Proof.
    intros x y z H H0.
    rewrite H.
    assumption.
  Qed. 

  (* x <> y est une abréviation de ~ (x = y) *)

  Lemma diff_eq : forall x y z:A, x <> y -> y = z -> x <> z.
  Proof.  
    intros.
    rewrite H0 in H.
    assumption. 
  Qed.
  
  Lemma L3 : forall x y z: A , x = y -> x <> z -> z <> y.
  Proof.
    intros.
    intro. 
     rewrite H1 in H0.
     apply H0.
     trivial.
   Qed.

   Lemma L4 : forall x y:A, f x <> f y -> x <> y.
   Proof.
     intros.
     intro H0.
     rewrite <- H0 in H.
     apply H.
     trivial.
   Qed.

End Egalite.

(* Exercice 3  de la feuille de TD N° 4 *)

(* Supprimer les "Admitted" (on admet la preuve complète) et les "admit" 
   (on admet le but courant) dans toutes les preuves qui suivent, et les
   compléter *)

Section Exercices_3_et_5.
  Variable A B: Type.
  Variables P Q : A -> Prop.
  Variable R : A -> B -> Prop.
  Variable X : Prop.

  Lemma Question1 : (forall x:A, P x /\ Q x) <->
                    (forall x:A, P x) /\ (forall x:A, Q x).
  Proof.
    split; intro H.
    - split.
      + intro x.
        destruct (H x).
        assumption.
      + intro x; destruct (H x); trivial.
    -  intro x; split.
      + destruct H as [Hp Hq].
        apply Hp.
      + destruct H.
        apply H0.
  Qed.

  Lemma Question2 : (forall x, P x) \/ (forall x, Q x) ->
                    forall x, P x \/ Q x.
  Proof.

    intros .
    destruct H.
    left.
    apply H.

    right.

    apply H.


    Qed.
  
  Lemma Question4 : (exists x:A, P x /\ Q x) ->
                    (exists x:A, P x) /\  (exists x:A, Q x).
  Proof.
    intros.
    destruct H.
    destruct H.
    split .
    exists x.
    assumption .
    exists x.
    assumption .

    Qed.

  Lemma Question6 : (exists x:A, P x \/ Q x) <->
                    (exists x:A, P x) \/   (exists x:A, Q x).
  Proof.

    split .
    intros .
    destruct H.
    destruct H.
    left.
    exists x.
    assumption .
    right .
    exists x.
    assumption .
    intros .
    destruct H.
    destruct H.
    exists x.
    left .
    assumption .
    destruct H.
    exists x.
    right .
    assumption .

    Qed.

  Section Question7.
    Hypothesis H : forall x, P x -> Q x.
    Hypothesis H0 : exists x, P x.

    Lemma L7 : exists x, Q x.
    Proof.
      destruct H0 as [x H1].
      exists x.
      forall_e H x.
      apply H2.
      assumption .
      Qed.

  End Question7.
 
  Lemma Question8 : forall x,  P x -> exists y,  P y.
  Proof.
    intros .
    exists x.
    assumption .

    Qed.
 
  Lemma Question10 : ~(exists x, P x) <-> forall x, ~ P x.
  Proof.
    split .
    intros .
    intro H1.
    apply H.
    exists x.
    assumption .
    intros .
    intro .
    destruct H0.
    forall_e H x.
    contradiction .
    Qed.

  Lemma Question11 : ((exists x, P x) -> X) <->
                     forall x, P x -> X.
  Proof.
  Admitted.

  Lemma Question12 :  (exists x:A, forall y:B, R x y)
                      -> (forall y:B, exists x:A, R x y).
  Proof. 

    intros .
    destruct H.
    exists x.
    forall_e H y.
    assumption .
    Qed.

  (* Sur l egalite *)
  Lemma eq_sym : forall x y:A, x = y -> y = x.
  Proof.
    intros x y H.
    rewrite H.     
    reflexivity.
  Qed.

  Lemma eq_trans : forall x y z:A, x = y -> y = z -> x = z.
  Proof.
    intros .
    rewrite H0 in H.
    assumption .
    Qed.

  (* De l'exercice 5 *)

  Definition A_est_vide := forall x:A, x <> x.

  
  Lemma exercice5_1 : A_est_vide -> forall x:A, P x.
  Proof.
    unfold A_est_vide. (* A compléter *)
    intros .
    forall_e H x.
    contradiction .
Qed.
  Lemma exercice_5_3 : (forall x y:A, x <> y) -> A_est_vide.
  Proof.
  Admitted.

  Section classic.
  Hypothesis exm : forall X : Prop, X \/ ~X.    

  Ltac add_exm  P :=
  let hname := fresh "exm" in
  assert(hname := exm  P).

  (* ne pas essayer de comprendre :
     applique le raisonnement par l'absurde classique 

  Transforme un but  "Gamma |- P " en 
                     "Gamma, ~P |- False" *)
  
  Ltac absurdK :=
    match goal with |- ?X =>
                    let hname := fresh "exm" in
                    assert(hname := exm  X);
                      destruct hname;[assumption| elimtype False]
    end.

  Lemma Question9 : ~ (forall x, P x) <-> exists x, ~ P x.
  Proof.   
    split.
    - intro H.
      absurdK.
      apply H.
      admit.    (*   remplacer le admit *)
    - 
  Admitted. (*   finir la preuve *)

  Section Exercice_5_2.
    Hypothesis H : ~ A_est_vide.
    Hypothesis H0 : forall x:A, P x.
    
    Lemma L_5_2 : exists x:A, P x. (* difficile *)
    Proof.
      unfold A_est_vide in H.
      assert (exists x:A, x = x).
      {  absurdK.
         admit.
      }
    Admitted.
    
  End Exercice_5_2.
  End classic. 
End Exercices_3_et_5.

Section drinkers_problem. (* Exercice 4 *)
  (* On se place en logique classique: on reprend donc le tiers exclus
     et l'absurde classique *)
  Hypothesis exm : forall X : Prop, X \/ ~X.    
  Ltac add_exm  P :=
  let hname := fresh "exm" in
  assert(hname := exm  P).
  
  Ltac absurdK :=
    match goal with |- ?X =>
                    let hname := fresh "exm" in
                    assert(hname := exm  X);
                      destruct hname;[assumption| elimtype False]
    end.

  Variable people : Type.
  Variable patron : people.

  Variable boit : people -> Prop.
  Theorem buveurs :
    exists p:people, boit p -> forall q, boit q.
  Proof.
    add_exm (forall q, boit q).
    destruct exm0.
    - exists patron;auto.
    -  assert (exists x:people, ~ boit x).
       {
         admit. 
       }
 Admitted.

End drinkers_problem.


 

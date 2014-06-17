class: center, middle
# MeteorFalls
---
# Présentation générale du projet

* Jeu multijoueurs
* Plusieurs équipes s'affrontent
* Chaque équipe est composée:
  * D'un commandant
  * De héros
* Environnement
  * Fantastique
  * Post-apocalyptique
  * Science-fiction
---

# L'équipe

À l'origine, l'équipe était composée par:
* Fabrice Bats
* Bastien Chevriaut
* Alexandre Ramel
* Thomas Loubiou
* Antoine Rose

---

# Choix Techniques

--
### Au niveau technologies

* C++
* Boost (Asio, Property Tree, Threads, …)
* Ogre 3D + SkyX, Hydrax, Paged Geometry
* CEGUI
* Lua
* Bullet Physics

--

### Au niveau architecture

* Utilisation d'un serveur global
* Modèle orienté objet
* Architecture Modéle/Vue
* Architecture réseau gouvernée par le serveur…
* Soutenue par le client pour fluidifier l'expérience du joueur


---

# Schémas général de l'architecture

---

# Quelques difficultés rencontrées

* Synchronisation d'un moteur physique sur le réseau
* Découplage de la création d'interface du reste du code
* Utiliser le plus de code commun possible entre le client et le serveur
* Pouvoir protéger l'accès à un serveur avec un mot de passe
* Comment bien gérer le réseau, afin de pouvoir fonctionner dans des conditions variées
* Comment gérer les différents états de jeu ?
* Comment gérer différentes architectures machines sur le réseau ?

---

# Pour conclure
Le but de ce projet n'étant pas d'avoir un jeu complet et fonctionnel, mais de comprendre et mettre en œuvre quelques technologies du domaine, nous avons atteint notre objectif.

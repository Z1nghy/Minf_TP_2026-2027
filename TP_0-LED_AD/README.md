# Minf_TP_0_LEDAD

## Configuration du timer 0

Pour faire fonctionner le chenillard, il est nécessaire d'utiliser un timer dans le code. Dans ce cas, nous utilisons le Timer 1.

Pour configurer le Timer 1, il est indispensable de calculer la Timer Period. Cette valeur correspond au nombre de ticks que le microcontrôleur compte avant de déclencher l'interruption. Pour obtenir un cycle de 100 ms, voici le calcul :

 <img width="318" height="86" alt="image" src="https://github.com/user-attachments/assets/3d03e106-8e02-49a7-96c4-c129a0f7648a" />

 
Avec t_voulu en microsecondes et un prescaler de 1, 8, 64 ou 256 (valeurs possibles pour le prescaler du Timer 1).

Comme le prescaler doit lui aussi être déterminé, nous supposons d'abord qu'il vaut 64 et nous vérifions si cette valeur convient :

<img width="706" height="148" alt="image" src="https://github.com/user-attachments/assets/46d06635-aa67-4dda-b564-8c0c44f33102" />

Ce calcul montre qu'un prescaler de 64 n'est pas adapté : la valeur obtenue dépasse la capacité du registre de période (65535 pour un timer 16 bits). Il faut donc utiliser un prescaler de 256. Voici le calcul de la Timer Period avec cette valeur :

<img width="737" height="110" alt="image" src="https://github.com/user-attachments/assets/fdf4d9f6-a841-4986-acd5-c78e4dc4bd92" />

Voici enfin la Timer Period saisie dans le configurateur Harmony, avec les valeurs demandées dans la donnée (priorité de l'interruption et implémentation du driver en mode STATIC) :

<img width="508" height="283" alt="Timer1" src="https://github.com/user-attachments/assets/8eaf76e2-48c4-4a3d-b837-69cbac25d7c6" />


## Mesure
La donnée nous demande de mesurer les quatre premieres leds du chenillard pour prouver son fonctionement ainsi que les trois secondes qu'il faut avant qu ele code ne s'active.
### Chenillard
Pour valider le fonctionnement du chenillard, les signaux des LED ont été mesurés à l'oscilloscope. La capture ci-dessous montre les voies correspondant aux LED0 à LED3.

<img width="1280" height="824" alt="Mesure TP0_LED0-1" src="https://github.com/user-attachments/assets/a4499538-e432-4190-9832-7917b6345368" />

Lorsque le chenillard atteint sa dernière LED, il repart en sens inverse au lieu de revenir directement à la première. C'est pourquoi la LED1 s'allume avant et après la LED0.

Bien que la durée d'allumage n'ait pas été mesurée avec les curseurs, les divisions de l'oscilloscope permettent de constater que chaque LED reste allumée environ 200 ms, ce qui correspond aux attentes de la donnée.


### Trois secondes
Pour valider le fonctionnement du délai de trois secondes dans l'interruption du Timer 1, le code a été modifié afin que la LED0 change d'état toutes les trois secondes.

<img width="1280" height="824" alt="Mesure 3s TP0" src="https://github.com/user-attachments/assets/1bb03065-8f5f-414d-849f-9287023d588a" />

La mesure effectuée à l'aide des curseurs confirme que le délai de trois secondes est bien respecté.

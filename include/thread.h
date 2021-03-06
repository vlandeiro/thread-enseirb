#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdio.h>

#define THREAD_CANCEL_ENABLE       0
#define THREAD_CANCEL_DISABLE      1


/* identifiant de thread */
typedef struct thread * thread_t;


/* recuperer l'identifiant du thread courant.
 */
thread_t thread_self(void);

/* creer un nouveau thread qui va exécuter la fonction func avec l'argument funcarg.
 * renvoie 0 en cas de succès, -1 en cas d'erreur.
 */
int thread_create(thread_t *newthread, void *(*func)(void *), void *funcarg);

/* passer la main à un autre thread.
 */
int thread_yield(void);

/* changer l'état d'annulation du thread entre activé et désactivé.
 * retourne 0 en cas de succès.
 */
int thread_setcancelstate(int state, int *oldstate);

/* changer le type d'annulation du thread entre asynchrone et déférré.
 * retourne 0 en cas de succès.
 */

int thread_cancel(thread_t thread);

/* attendre la fin d'exécution d'un thread.
 * la valeur renvoyée par le thread est placée dans *retval.
 * si retval est NULL, la valeur de retour est ignorée.
 */
int thread_join(thread_t thread, void **retval);

/* terminer le thread courant en renvoyant la valeur de retour retval.
 * cette fonction ne retourne jamais.
 *
 * L'attribut noreturn aide le compilateur à optimiser le code de
 * l'application (élimination de code mort). Attention à ne pas mettre
 * cet attribut dans votre interface tant que votre thread_exit()
 * n'est pas correctement implémenté (il ne doit jamais retourner).
 */
void thread_exit(void *retval) __attribute__ ((__noreturn__));

#endif /* __THREAD_H__ */

/*
----------------Choice Of Destiny----------------
    BOUDAHBA Ayyoub - BOSSUS Quentin


If you have any issues understanding the code or the story, you can contact the following people:

quentin.bossus@etu.univ-littoral.fr
ayyouv.boudahba@etu-univ-littoral.fr
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* struct of the protagonist / inventory */
typedef struct {
    char protagonist_name[21];
    int protagonist_gold;
    int protagonist_HP_potion;
    int protagonist_strength_potion;
    int protagonist_trap_remover;
    int protagonist_mystery_key;
    int protagonist_HP;
    int protagonist_strength;
    int protagonist_exp;
} protagonist;


/* Function to display the narration */
void story_telling(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("missing file %s\n", file_name);
        return;
    }
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        }
    fclose(file);
}


/* Function to display the number of exp before a level up / If level up, display "level up" */
void experience(protagonist *p, int exp_gain, char *path_prefix) {
    char file_exp_gain[100], file_level_up[100];
    sprintf(file_exp_gain, "%sexp_gain.txt", path_prefix);
    sprintf(file_level_up, "%slevel_up.txt", path_prefix);

    p->protagonist_exp = p->protagonist_exp + exp_gain;
    story_telling(file_exp_gain);
    printf("%d/100", p->protagonist_exp);

    if(p->protagonist_exp >= 100) {
        story_telling(file_level_up);
        p->protagonist_exp = 0;
        p->protagonist_HP = p->protagonist_HP + 5;
        p->protagonist_strength = p->protagonist_strength + 2;
    }
}


/* Function 20% of fleeing durint battle */
int flee(char *path_prefix) {
    int randomValue = rand() % 100; /* Random value between 0 and 99 */
    int fleeChance = 20; /* Flee chance of 20% */
    char file_flee_failed[100], file_flee_success[100];

    sprintf(file_flee_failed, "%sflee_failed.txt", path_prefix);
    sprintf(file_flee_success, "%sflee_success.txt", path_prefix);

    if (randomValue < fleeChance) {
        story_telling(file_flee_success);
        return 1;
    } else {
        story_telling(file_flee_failed);
        return 0;
    }
}


/* Function 20% of critical hit durint battle */
int crit(char *path_prefix) {
    int randomValue = rand() % 100; /* Random value between 0 and 99 */
    int CritChance = 20; /* Crit chance of 20% */
    char file_crit_hit[100];

    sprintf(file_crit_hit, "%scrit_hit.txt", path_prefix);

    if (randomValue < CritChance) {
        story_telling(file_crit_hit);
        return 1;
    } else {
        return 0;
    }
}


/* Function to calculate and print gold amount the player gets */
void add_gold(protagonist *p, int amount, char *path_prefix) {
    char file_gold_update[200];
    sprintf(file_gold_update, "%sgold_update.txt", path_prefix);

    p->protagonist_gold = p->protagonist_gold + amount;
    story_telling(file_gold_update);
    printf("%d\n", p->protagonist_gold);
}


/* Function to display the amount of gold */
int print_gold_amount(protagonist *p) {
    return p->protagonist_gold;
}


/* Function to display Heal Point of Protagonist */
void print_protagonist_HP(protagonist *p, char *path_prefix) {
    char file_print_protagonist_HP[100];
    sprintf(file_print_protagonist_HP, "%sprint_protagonist_HP.txt", path_prefix);

    story_telling(file_print_protagonist_HP);
}


/* Function to update the number of item "HP_POTION" */
void add_HP_potion(protagonist *p, int number, char *path_prefix) {
    p->protagonist_HP_potion = p->protagonist_HP_potion + number;
}


/* Function to update the number of item "STRENGtH_POTION" */
void add_strength_potion(protagonist *p, int number, char *path_prefix) {
    p->protagonist_strength_potion = p->protagonist_strength_potion + number;
}


/* Function to update the number of item "TRAP_REMOVER" */
void add_trap_remover(protagonist *p, int number, char *path_prefix) {
    p->protagonist_trap_remover = p->protagonist_trap_remover + number;
}


/* Function to update the number of item "MYSTERY_KEY" */
void add_mystery_key(protagonist *p, int number, char *path_prefix) {
    p->protagonist_mystery_key = p->protagonist_mystery_key + number;
}




/* Function to display and interact with the shop */
void shop(protagonist *p, char *path_prefix) {
    int choice;
    char file_print_shop[400], file_must_choose[100], file_not_enough[100];
    int cost_HP = 15, cost_strength = 25, cost_trap_remover = 30, cost_mystery_key = 40;

    /* All files used here */
    sprintf(file_print_shop, "%sprint_shop.txt", path_prefix);
    sprintf(file_must_choose, "%smust_choose.txt", path_prefix);
    sprintf(file_not_enough, "%snot_enough.txt", path_prefix);


    /* Buy or leave the shop */
    do {
        story_telling(file_print_shop);
        scanf("%d", &choice);
        printf("\033[H\033[J");
        switch (choice) {

        /* HP Potion */
        case 1:
            if(print_gold_amount(p) >= cost_HP) {
                add_HP_potion(p, 1, path_prefix);
                p->protagonist_gold = p->protagonist_gold - cost_HP;
            } else {
                story_telling(file_not_enough);
            }
            break;

        /* Strength Potion */
        case 2:
            if(print_gold_amount(p) >= cost_strength) {
                add_strength_potion(p, 1, path_prefix);
                p->protagonist_gold = p->protagonist_gold - cost_strength;
            } else {
                story_telling(file_not_enough);
            }
            break;

        /* Trap Remover */
        case 3:
            if(print_gold_amount(p) >= cost_trap_remover) {
                add_trap_remover(p, 1, path_prefix);
                p->protagonist_gold = p->protagonist_gold - cost_trap_remover;
            } else {
                story_telling(file_not_enough);
            }
            break;

        /* Mystery Key */
        case 4:
            if(print_gold_amount(p) >= cost_mystery_key) {
                add_mystery_key(p, 1, path_prefix);
                p->protagonist_gold = p->protagonist_gold - cost_mystery_key;
            } else {
                story_telling(file_not_enough);
            }
            break;

        /* avoid to display default */
        case 5:
            break;
        
        default:
            story_telling(file_must_choose);
            break;
        }
    }while(choice != 5);
}




/* Function to display the battle options */
int battle(protagonist *p, char *path_prefix) {
    int mob_HP = 10;
    int choice;
    int crit_damage = p->protagonist_strength * 2;
    /* Initialize all files */
    char file_fight[200], file_print_mob_HP[100], file_attack[200], file_item[200], file_potion[100], file_no_potion[200],
        file_monster_attack[200], file_win[200], file_lost[200];

    /* All files used here */
    sprintf(file_fight, "%sfight.txt", path_prefix);
    sprintf(file_print_mob_HP, "%sprint_mob_HP.txt", path_prefix);   
    sprintf(file_attack, "%sattack.txt", path_prefix);
    sprintf(file_item, "%sitem.txt", path_prefix);
    sprintf(file_potion, "%spotion.txt", path_prefix);
    sprintf(file_no_potion, "%sno_potion.txt", path_prefix);
    sprintf(file_monster_attack, "%smonster_attack.txt", path_prefix);
    sprintf(file_win, "%swin.txt", path_prefix);
    sprintf(file_lost, "%slost.txt", path_prefix);


    /* Battle option */
    do {
        story_telling(file_fight);
        while (getchar() != '\n');
        scanf("%d", &choice);
        printf("\033[H\033[J");
        switch (choice) {

            /* Attack */
            case 1 :
                story_telling(file_attack);
                /* Critical Damage */
                if (crit(path_prefix)) {
                    mob_HP = mob_HP - crit_damage;
                } else {
                    mob_HP = mob_HP - p->protagonist_strength;
                }
                break;

            /* Use Item */
            case 2 :
                story_telling(file_item);
                scanf("%d", &choice);
                printf("\033[H\033[J");
                switch (choice) {

                    /* HP Potion */
                    case 1:
                        if (p->protagonist_HP_potion > 0) {
                            story_telling(file_potion);
                            p->protagonist_HP = p->protagonist_HP + 5;
                            add_HP_potion(p, -1, path_prefix);
                            break;
                        } else {
                            story_telling(file_no_potion);
                            break;
                        }
                    
                    /* Strength Potion */
                    case 2:
                        if (p->protagonist_strength_potion > 0) {
                            story_telling(file_potion);
                            p->protagonist_strength = p->protagonist_strength + 2;
                            add_strength_potion(p, -1, path_prefix);
                            break;
                        } else {
                            story_telling(file_no_potion);
                            break;
                        }

                    default:
                        story_telling(file_no_potion);
                        break;
                }
                break;

            /* Try to Flee */
            case 3 :
                if (flee(path_prefix)) {
                    return 1;
                }
                break;
            
            /* Default : attack */
            default:
                story_telling(file_attack);
                /* Critical Damage */
                if (crit(path_prefix)) {
                    mob_HP = mob_HP - crit_damage;
                } else {
                    mob_HP = mob_HP - p->protagonist_strength;
                }
                break;
        }

        /* Verify if the mob die / avoid "-2HP" if he die */
        if(mob_HP > 0) {
            story_telling(file_monster_attack);
            p->protagonist_HP = p->protagonist_HP - 2;

            print_protagonist_HP(p, path_prefix);
            printf("%d", p->protagonist_HP);
            story_telling(file_print_mob_HP);
            printf("%d\n", mob_HP);
        }
    } while (p->protagonist_HP > 0 && mob_HP > 0);


    /* Result of the fight */
    if(p->protagonist_HP > mob_HP) {
        story_telling(file_win);
        add_gold(p, 15, path_prefix);
        experience(p, 25, path_prefix);
        return 1;
    } else {
        story_telling(file_lost);
        return 0;
    }
}




/* Function to display the story based on the selected version */
void story(protagonist *p, char *path_prefix) {
    int i = 0;
    char choice, event_choice;
    /* Initialize all files */
    char file_chapter1[400], file_straight_path[200], file_empty_room[200], file_fight_start[200], file_impossible_choice[200], file_post_fight[200], 
        file_gold_room[300], file_shop_room[400], file_skip_shop[200], file_item_room[200], file_pnj_path_room[500], file_pnj_path_error[200],
        file_pnj_path_good_answer[300], file_pnj_path_bad_answer[200], file_trap_room[200], file_trap_dmg[100], file_trap_remove[100], file_map_room[400], 
        file_map[3600], file_error_map[200], file_event[200], file_skip_event[200], file_dual_path[200], file_final_path1[300], file_end_chapter1[400],
        file_name[100], file_end_chapter2[500], file_final_path2[500];


    /* All files used here */
    sprintf(file_chapter1, "%schapter1.txt", path_prefix);
    sprintf(file_straight_path, "%sstraight_path.txt", path_prefix);
    sprintf(file_empty_room, "%sempty_room.txt", path_prefix);
    sprintf(file_fight_start, "%sfight_start.txt", path_prefix);
    sprintf(file_impossible_choice, "%simpossible_choice.txt", path_prefix);
    sprintf(file_post_fight, "%spost_fight.txt", path_prefix);
    sprintf(file_gold_room, "%sgold_room.txt", path_prefix);
    sprintf(file_item_room, "%sitem_room.txt", path_prefix);
    sprintf(file_shop_room, "%sshop_room.txt", path_prefix);
    sprintf(file_skip_shop, "%sskip_shop.txt", path_prefix);   
    sprintf(file_pnj_path_room, "%spnj_path_room.txt", path_prefix);
    sprintf(file_pnj_path_good_answer, "%spnj_path_good_answer.txt", path_prefix);
    sprintf(file_pnj_path_bad_answer, "%spnj_path_bad_answer.txt", path_prefix);
    sprintf(file_pnj_path_error, "%spnj_path_error.txt", path_prefix);
    sprintf(file_trap_room, "%strap_room.txt", path_prefix);
    sprintf(file_trap_remove, "%strap_remove.txt", path_prefix);
    sprintf(file_trap_dmg, "%strap_dmg.txt", path_prefix);
    sprintf(file_map_room, "%smap_room.txt", path_prefix);
    sprintf(file_map, "%smap.txt", path_prefix);
    sprintf(file_error_map, "%serror_map.txt", path_prefix);
    sprintf(file_event, "%sevent.txt", path_prefix);
    sprintf(file_skip_event, "%sskip_event.txt", path_prefix);
    sprintf(file_dual_path, "%sdual_path.txt", path_prefix);
    sprintf(file_final_path1, "%sfinal_path1.txt", path_prefix);
    sprintf(file_end_chapter1, "%send_chapter1.txt", path_prefix);
    sprintf(file_name, "%sname.txt", path_prefix);
    sprintf(file_end_chapter2, "%send_chapter2.txt", path_prefix);
    sprintf(file_final_path2, "%sfinal_path2.txt", path_prefix);


    /* Beginning of the story */
    story_telling(file_chapter1);
    do {
        while(getchar() != '\n');
        scanf("%c", &choice);
        switch(choice) {

            /* Left Choice1 */
            case 'l':
            case 'L':
            case 'g':
            case 'G':
                printf("\033[H\033[J");
                story_telling(file_fight_start);
                if (battle(p, path_prefix) == 0) {
                    return;
                }
                story_telling(file_post_fight);

                do {
                    while (getchar() != '\n');
                    scanf("%c", &choice);
                    printf("\033[H\033[J");
                    switch (choice) {

                        /* Left Choice2 */
                        case 'l':
                        case 'L':
                        case 'g':
                        case 'G':
                            story_telling(file_gold_room);
                            while (getchar() != '\n');
                            scanf("%c", &event_choice);
                            printf("\033[H\033[J");
                            switch (event_choice) {

                                /* Accept or rejet */
                                case 'o':
                                case 'O':
                                case 'y':
                                case 'Y':
                                    story_telling(file_event);
                                    add_gold(p, 30, path_prefix);

                                    /* "Press enter to continue" */
                                    printf("\n...\n");
                                    while (getchar() != '\n');
                                    getchar();
                                    /* "Press enter to continue" */

                                    printf("\033[H\033[J");
                                    break;
                                
                                default:
                                    story_telling(file_skip_event);

                                    /* "Press enter to continue" */
                                    printf("\n...\n");
                                    while (getchar() != '\n');
                                    getchar();
                                    /* "Press enter to continue" */

                                    printf("\033[H\033[J");
                                    break;
                            }
                            story_telling(file_straight_path);
                            story_telling(file_shop_room);
                            scanf("%c", &event_choice);
                            switch (event_choice) {

                                /* Accept or rejet */
                                case 'o':
                                case 'O':
                                case 'y':
                                case 'Y':
                                    printf("\033[H\033[J");
                                    shop(p, path_prefix);
                                    break;
                                
                                default:
                                    printf("\033[H\033[J");
                                    story_telling(file_skip_shop);
                                    break;
                            }
                            break;
                            
                        /* Right Choice2 */
                        case 'r':
                        case 'R':
                        case 'd':
                        case 'D':
                            story_telling(file_item_room);
                            story_telling(file_straight_path);
                                        
                            /* "Press enter to continue" */
                            printf("\n...\n");
                            while (getchar() != '\n');
                            getchar();
                            /* "Press enter to continue" */

                            printf("\033[H\033[J");
                            story_telling(file_pnj_path_room);
                            do {
                                printf("\n1) ");
                                scanf("%c", &choice);
                                printf("\033[H\033[J");
                                switch (choice) {

                                    /* LEFT */
                                    case 'l':
                                    case 'L':
                                    case 'g':
                                    case 'G':
                                        
                                        while (getchar() != '\n');
                                        printf("2) ");
                                        scanf("%c", &choice);
                                        printf("\033[H\033[J");
                                        switch (choice) {

                                            /* LEFT - LEFT */
                                            case 'l':
                                            case 'L':
                                            case 'g':
                                            case 'G':
                                                story_telling(file_pnj_path_bad_answer);
                                                break;

                                            /* LEFT - RIGHT */
                                            case 'r':
                                            case 'R':
                                            case 'd':
                                            case 'D':
                                                story_telling(file_pnj_path_good_answer);
                                                add_mystery_key(p, 1, path_prefix);
                                                break;
                                            
                                            default:
                                                story_telling(file_pnj_path_error);
                                                break;
                                        }
                                        break;
                                    
                                    /* RIGHT */
                                    case 'r':
                                    case 'R':
                                    case 'd':
                                    case 'D':
                                        
                                        while (getchar() != '\n');
                                        printf("\n2) ");
                                        scanf("%c", &choice);
                                        printf("\033[H\033[J");
                                        switch (choice) {

                                            /* RIGHT - LEFT */
                                            case 'l':
                                            case 'L':
                                            case 'g':
                                            case 'G':
                                                story_telling(file_pnj_path_bad_answer);
                                                break;

                                            /* RIGHT - RIGHT */
                                            case 'r':
                                            case 'R':
                                            case 'd':
                                            case 'D':
                                                story_telling(file_pnj_path_bad_answer);
                                                break;
                                            
                                            default:
                                                story_telling(file_pnj_path_error);
                                                break;
                                        }
                                        break;
                                    
                                    default:
                                        story_telling(file_pnj_path_error);
                                        break;
                                }
                            }while(choice != 'l' && choice != 'L' && choice != 'g' && choice != 'G' && choice != 'r' && choice != 'R' && choice != 'd' && choice != 'D');
                            break;
                            
                        default:
                            story_telling(file_impossible_choice);
                            break;
                    }
                } while (choice != 'l' && choice != 'L' && choice != 'g' && choice != 'G' && choice != 'r' && choice != 'R' && choice != 'd' && choice != 'D' && event_choice != 'o' && event_choice != 'O' && event_choice != 'y' && event_choice != 'Y');
                break;

            /* Right Choice1 */
            case 'r':
            case 'R':
            case 'd':
            case 'D':
                printf("\033[H\033[J");
                story_telling(file_empty_room);
                story_telling(file_straight_path);

                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                getchar();
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                story_telling(file_item_room);
                add_HP_potion(p, 1, path_prefix);
                story_telling(file_dual_path);
                scanf("%c", &choice);
                switch (choice) {

                    /* Left Choice3 */
                    case 'l':
                    case 'L':
                    case 'g':
                    case 'G':
                        printf("\033[H\033[J");
                        story_telling(file_trap_room);
                        if (p->protagonist_trap_remover > 0) {
                            story_telling(file_trap_remove);
                            p->protagonist_trap_remover = p->protagonist_trap_remover - 1;
                        } else {    
                            story_telling(file_trap_dmg);
                            p->protagonist_HP = p->protagonist_HP - 5;
                        }

                        /* "Press enter to continue" */
                        printf("\n...\n");
                        while (getchar() != '\n');
                        getchar();
                        /* "Press enter to continue" */

                        printf("\033[H\033[J");

                        break;
                    
                    /* Right Choice3 */
                    case 'r':
                    case 'R':
                    case 'd':
                    case 'D':
                        printf("\033[H\033[J");
                        story_telling(file_map_room);
                        do {
                            while (getchar() != '\n');
                            scanf("%c", &event_choice);
                            switch (event_choice) {
                                case 'm':
                                case 'M':
                                    printf("\033[H\033[J");
                                    story_telling(file_map);

                                    /* "Press enter to continue" */
                                    printf("\n...\n");
                                    while (getchar() != '\n');
                                    getchar();
                                    /* "Press enter to continue" */

                                    break;
                                
                                default:
                                    printf("\033[H\033[J");
                                    story_telling(file_error_map);
                                    break;
                            }
                        }while(event_choice != 'M' && event_choice != 'm');
                        break;
                    
                    default:
                        story_telling(file_impossible_choice);
                        break;
                }
                break;
                
            default:
                story_telling(file_impossible_choice);
                break;
        }
    }while (choice != 'l' && choice != 'L' && choice != 'g' && choice != 'G' && choice != 'r' && choice != 'R' && choice != 'd' && choice != 'D');

    story_telling(file_final_path1);
    
    /* "Press enter to continue" */
    printf("\n...\n");
    getchar();
    /* "Press enter to continue" */

    printf("\033[H\033[J");
    story_telling(file_end_chapter1);
    scanf("%s", p->protagonist_name);
    story_telling(file_name);
    printf("%s", p->protagonist_name);
    /* End of chapter 1 */

    /* "Press enter to continue" */
    printf("\n...\n");
    while (getchar() != '\n');
    getchar();
    /* "Press enter to continue" */

    printf("\033[H\033[J");


    /* Beginning of chapter 2 : Random room */
    for (i = 0; i < 5; i++) {
        int randomValue = rand() % 6; /* Random value between 0 and 5 */
        
        /* Different room depending of random function */
        switch (randomValue) {
            case 0:
                story_telling(file_empty_room);

                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                break;

            case 1:
                story_telling(file_gold_room);
                scanf("%c", &event_choice);
                printf("\033[H\033[J");
                switch (event_choice) {

                    /* Accept or rejet */
                    case 'o':
                    case 'O':
                    case 'y':
                    case 'Y':
                        story_telling(file_event);
                        add_gold(p, 30, path_prefix);
                        break;

                    default:
                        story_telling(file_skip_event);
                        break;
                }

                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                break;

            case 2:
                story_telling(file_trap_room );
                if (p->protagonist_trap_remover > 0) {
                    story_telling(file_trap_remove);
                    p->protagonist_trap_remover = p->protagonist_trap_remover - 1;
                } else {    
                    story_telling(file_trap_dmg);
                    p->protagonist_HP = p->protagonist_HP - 5;
                }
                
                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */
                
                printf("\033[H\033[J");
                break;

            case 3:
                story_telling(file_item_room);
                p->protagonist_HP_potion = p->protagonist_HP_potion + 1;
                
                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                break;

            case 4:
                story_telling(file_fight_start);
                if (battle(p, path_prefix) == 0) {
                    return;
                }
                
                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                break;

            case 5:
                story_telling(file_shop_room);
                scanf("%c", &event_choice);
                switch (event_choice) {
                    case 'o':
                    case 'O':
                    case 'y':
                    case 'Y':
                        printf("\033[H\033[J");
                        shop(p, path_prefix);
                        break;

                    default:
                        printf("\033[H\033[J");
                        story_telling(file_skip_shop);
                        break;
                }
                
                /* "Press enter to continue" */
                printf("\n...\n");
                while (getchar() != '\n');
                /* "Press enter to continue" */

                printf("\033[H\033[J");
                break;
        }
    }
    story_telling(file_final_path2);

    /* "Press enter to continue" */
    printf("\n...\n");
    while (getchar() != '\n');
    getchar();
    /* "Press enter to continue" */

    printf("\033[H\033[J");
    story_telling(file_end_chapter2);

    printf("Thank you for playing the beta test !");

    /* End of chapter 2 */
}




/* Function to start Great Britain version */
void GB_version(protagonist *p) {
    printf("\033[H\033[J");
    story(p, "GB/GB-");
}


/* Function to start French version */
void FR_version(protagonist *p) {
    printf("\033[H\033[J");
    story(p, "FR/FR-");
}


/* Function to select the language version */
void select_language(protagonist *p) {
    int language;

    printf("\033[H\033[J");
    printf("Please choose the language for the game : \nGreat Britain = 1\nFrench = 2\n\n");
    do {
        scanf("%d", &language);
        switch (language) {
            case 1 :
                GB_version(p);
                break;

            case 2 :
                FR_version(p);
                break;

            default :
                printf("You must choose a language !\n");
                while (getchar() != '\n');
        }
    }while(language < 1 || language > 2);
}


/* Main */
int main() {
    protagonist p = {"\0", 0, 0, 0, 0, 0, 30, 3, 0};
    srand(time(NULL));
    select_language(&p);

    return 0;
}
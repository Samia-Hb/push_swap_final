/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:36:36 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/04 12:14:23 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int find_max_elememt(Stack *stackB)//done
{
    int     max_element;
    Stack*  courant;

    max_element = INT_MIN;
    courant = stackB;
    while (courant)
    {
        if (courant->data > max_element)           
            max_element = courant->data;            
        courant = courant->next;
    }
    return (max_element);
}

int calculate_Min_element(Stack *stackA,Stack *stackB)//done
{
    int Min_element;
    Stack *courant;
    int Min_count;
    int i;
    int *count;

    i = 0;
    Min_count = INT_MAX;
    courant = stackA;
    Min_element = stackA->data;
    count = malloc(ft_lstsize(stackA) * sizeof(int));
    if (!count)
        return 0;
    while (i < ft_lstsize(stackA) && courant != NULL)
    {
        count[i] = calcule_nbr_mouvement_stackA(stackA, stackB, courant->data);
        if(count[i] < Min_count)
        {
            Min_count = count[i];
            Min_element = courant->data;
        }
        i++;
        courant = courant -> next;
    }
    free(count);
    return(Min_element);
}

void sort_stackb_before(Stack** stackB, int pos)//done
{
    if (pos == 0)
        return ;
    else if (pos <= ft_lstsize(*stackB) / 2)
    {
        while (pos != 0)
        {
            rb(stackB);
            printf("rb\n");
            pos--;
        }
    }
    else if (pos >= ft_lstsize(*stackB) / 2)
    {
        while(pos != ft_lstsize(*stackB) - 1)
        {
            rrb(stackB);
            printf("rrb\n");
            pos++;
        }
        if(pos == ft_lstsize(*stackB) - 1)
        {
            rrb(stackB);
            printf("rrb\n");
        }
    }
}
void push_the_min(Stack** stackA, Stack** stackB, int element)//done
{
    if(pos (*stackA,element) == 1)
    {
        sa(*stackA);
        printf("sa\n");
    }
    else if (pos(*stackA,element) > 1)
    {
        while (pos(*stackA,element) != 0)
        {
            if (pos(*stackA,element) <= ft_lstsize(*stackA) / 2)
            {
                ra(stackA);
                printf("ra\n");
            }
            else
            {
                rra(stackA);
                printf("rra\n");
            }
        }
    }
    sort_stackb_before(stackB, find_closest_pos(*stackB, element));
    pb(stackA, stackB);
}

void sort_stackB(Stack **stackB)//done
{
    int position;
    int max_element;

    max_element = find_max_elememt(*stackB);
    position = pos(*stackB,max_element);
    while (position != 0)
    {
        if(position <= ft_lstsize(*stackB) / 2)
        {
            rb(stackB);
            printf("rb\n");
        }
        else if(position > ft_lstsize(*stackB) / 2)
        {
            rrb(stackB);
            printf("rrb\n");
        }
        position = pos(*stackB,max_element);
    }
}

void push_to_stackB(Stack **stackA,Stack **stackB)//done
{
    int size ;
    int Min_element;
    int full_size;

    full_size = ft_lstsize(*stackA);
    pb(stackA, stackB);
    printf("pb\n");
    pb(stackA, stackB);
    printf("pb\n");
    size = ft_lstsize(*stackA);
    while (size != 0 && ft_lstsize(*stackB) != full_size)
    {
        Min_element = calculate_Min_element(*stackA, *stackB);
        push_the_min(stackA, stackB, Min_element);
        printf("pb\n");
        size++;
    }
    if (!isStackSorted(*stackB,0))
        sort_stackB(stackB);
}


int Min_element(Stack *stackA)//done
{
    int min_element;
    
    min_element = INT_MAX;
    while (stackA)
    {
        if(stackA->data < min_element)
            min_element = stackA->data;
        stackA = stackA -> next;
    }
    return (min_element);
}

            //100 number
// 43 17 89 52 76 11 65 31 94 24 5 68 82 39 20 73 57 8 96 61 14 50 28 91 36 78 2 47 85 19 60 27 88 45 10 83 55 29 75 22 93 3 67 33 87 16 41 7 51 13 74 59 26 80 48 35 99 64 21 90 38 98 56 15 81 42 6 72 30 95 23 79 49 4 77 32 66 1 84 18 58 12 70 25 92 37 63 9 69 53 97 34 86 40 62 54 71 46 100 44 0
            //500 number
// 43 17 89 52 76 11 65 31 94 24 5 68 82 39 20 73 57 8 96 61 14 50 28 91 36 78 2 47 85 19 60 27 88 45 10 83 55 29 75 22 93 3 67 33 87 16 41 7 51 13 74 59 26 80 48 35 99 64 21 90 38 98 56 15 81 42 6 72 30 95 23 79 49 4 77 32 66 1 84 18 58 12 70 25 92 37 63 9 69 53 97 34 86 40 62 54 71 46 100 44 0 101 126 116 111 104 137 109 138 124 145 119 150 131 114 120 128 155 133 105 106 113 108 118 125 134 136 112 103 102 107 141 135 148 144 146 122 123 139 127 121 140 115 143 151 147 110 132 130 129 142 149 153 156 154 157 158 164 167 176 159 163 166 160 161 170 168 169 165 175 173 162 174 171 177 172 180 187 179 183 182 184 189 186 185 188 190 194 196 195 198 191 200 201 199 197 202 206 207 205 204 203 213 212 211 210 209 208 214 218 215 216 219 217 222 221 223 220 225 226 229 230 227 228 224 232 234 233 231 235 238 239 236 240 237 242 241 244 243 245 246 248 247 251 249 250 252 254 253 255 257 256 260 258 259 261 263 262 265 264 267 268 269 270 266 272 274 275 273 271 278 277 276 281 279 280 283 282 285 284 287 288 286 290 289 292 291 294 295 293 297 298 299 296 301 300 303 302 305 304 307 306 309 308 312 310 311 314 313 316 317 315 319 318 322 321 323 320 326 325 324 328 327 331 330 329 334 333 332 336 335 339 337 338 342 341 340 345 343 347 346 349 350 348 344 353 352 351 356 355 354 359 358 357 361 360 364 365 363 368 367 366 371 369 373 370 375 374 377 376 379 380 382 381 384 383 386 385 388 387 390 389 393 391 395 394 392 398 397 396 400 399 403 402 401 406 405 404 409 408 407 412 411 410 415 414 413 418 417 416 421 420 419 424 423 422 427 426 425 430 429 428 433 432 431 436 435 434 439 437 441 440 443 442 445 444 447 446 449 448 452 451 450 455 454 453 458 457 456 461 460 459 464 463 462 467 466 465 470 469 468 473 472 471 476 475 474 479 478 477 482 481 480 485 484 483 488 487 486 491 490 489 494 493 492 497 496 495 500 499 498 503 502 501 506 505 504 509 508 507 512 511
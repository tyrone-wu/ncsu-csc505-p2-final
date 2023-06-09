/* 
 *  Mersenne Twister (MT19937) - Header File
 *  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura
 *  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 *  email: m-mat [at] math.sci.hiroshima-u.ac.jp
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *  
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *  
 *    3. The names of its contributors may not be used to endorse or promote 
 *       products derived from this software without specific prior written 
 *       permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __RANDOM_H
#define __RANDOM_H


/* Generator intialization. */
void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);

/* Random integer generation. */
unsigned long genrand_int32(void);
long genrand_int31(void);

/* Random real number generation. */
double genrand_real1(void); /* [0,1] */
double genrand_real2(void); /* [0,1) */
double genrand_real3(void); /* (0,1) */
double genrand_res53(void); /* [0,1) with 53-bit resolution */


#endif /* __RANDOM_H */


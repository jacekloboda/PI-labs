#include <stdio.h>

#define N 10

typedef enum {S0, S1} stany;
typedef enum {Z0, Z1} symbole;

symbole pamiec[N];
int poz;
stany stan;

void restart(void)
{
				for( int i = 0; i < N; i++ )
				{
								pamiec[i] = Z0;
				}

				stan = S0;
				poz = 0;

				return;
}

void print_pamiec(void)
{
				printf( "S%d: ", (stan == S0) ? 0 : 1 );
				
				for(int i = 0; i < N; i++)
				{
							if(i == poz)	
							{
											printf("(%d)", (pamiec[i] == Z0) ? 0 : 1);
							}
							else
							{
											
											printf("%d", (pamiec[i] == Z0) ? 0 : 1);
							}
				}

				printf("\n");
				
				return;
}

void krok(void)
{
				print_pamiec();

				switch(stan)
				{
								case S0: 
												if(pamiec[poz] == Z0)
												{
																pamiec[poz] = Z1;
																stan = S1;
																poz = ( poz<N-1 ) ? poz+1 : 0;
												}
												else
												{
																pamiec[poz] = Z1;
																poz = ( poz > N-1 ) ? poz-1 : N-1;
												}
												break;
								
								case S1:
												if(pamiec[poz] == Z0 )
												{
																stan = S0;
																poz = ( poz<N-1 ) ? poz+1 : 0;
												}
												else
												{
																poz = ( poz < N-1 ) ? poz-1 : N-1;

																
												}

				}


				return;
}

int main(void)
{
				restart();

				while(1)
				{
								krok();

								if(pamiec[poz] == Z1 && stan == S1 )
								{
												break;
								}
				}

				return 0;
}

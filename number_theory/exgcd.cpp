int exgcd(int a,int b,int&x,int&y){
  if(!b)return x=1,y=0,a;
  int d=exgcd(b,a%b,x,y),t=x;
  return x=y,y=t-a/b*y,d;
}
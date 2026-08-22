/**
 * Author: nor, compressed by Arthur Botelho and ChatGPT
 * Source: Harold N. Gabow, "The Weighted Matching Approach to Maximum Cardinality Matching" (2017)
 * Description: Maximum cardinality matching in a general graph. Vertices are 0-indexed.
 * solve() returns the size, get() returns the edges.
 * Time: O(sqrt(n) m log_{max(2,1+m/n)} n)
 * Memory: O(n+m)
 * Status: randomized against brute force, tested at Graph of Love (600 ms, N = M = $10^5$), 2s at CSES Tree Matching
 */
#pragma once

struct GeneralMatching {
	struct Edge { int u,v; };
	static constexpr int INF=1<<30, INNER=-1, FREE=0;
	int n,nh,ql,qr,hs,hl,sp,tim,aug,cc,oid;
	vi off,q,mt,pot,lab,dsu,lh,ln,bh,bn,st;
	vector<Edge> ed,lk,hist;
	GeneralMatching(int N, const vector<Edge>& in):
		n(N),nh(N/2),off(n+2),ed(2*sz(in)) {
		for(auto e:in){
			int a=e.u+1,b=e.v+1;
			off[a+1]++; off[b+1]++;
		}
		rep(i,1,n+2)off[i]+=off[i-1];
		for(auto e:in){
			int a=e.u+1,b=e.v+1;
			ed[off[a]++]={a,b};
			ed[off[b]++]={b,a};
		}
		for(int i=n+1;i;i--)off[i]=off[i-1];
		off[0]=0;
	}
	int find(int x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
	void push(vi& h,vi& nx,int a,int b){nx[b]=h[a]; h[a]=b;}
	void reset(){tim=0; aug=INF; cc=0; oid=1; hs=hl=0;}
	void clear(){
		ql=qr=0; rep(i,tim,nh+1)lh[i]=-1;
		rep(i,1,n+1)pot[i]=1,dsu[i]=i,bh[i]=-1;
	}
	void grow(int x,int y,int z){
		lab[y]=INNER; pot[y]=tim; lk[z]={x,y};
		lab[z]=lab[x]; pot[z]=tim+1; q[qr++]=z;
	}
	void contract(int x,int y){
		int a=find(x),b=find(y),h=-(++cc)+INNER,lca=-1;
		lab[mt[a]]=lab[mt[b]]=h;
		for(;;){
			if(mt[b])swap(a,b);
			a=lca=find(lk[a].u);
			if(lab[mt[a]]==h)break;
			lab[mt[a]]=h;
		}
		for(int v:{dsu[x],dsu[y]})
			for(;v!=lca;v=dsu[lk[v].u]){
				int w=mt[v];
				lk[w]={x,y}; lab[w]=lab[x];
				pot[w]=1+(tim-pot[w])+tim;
				q[qr++]=w;
				dsu[v]=dsu[w]=lca;
				hist[hl++]={v,lca};
				hist[hl++]={w,lca};
			}
	}
	bool search(){
		while(ql<qr){
			int x=q[ql++],lx=lab[x],px=pot[x],bx=find(x);
			for(int i=off[x];i<off[x+1];i++){
				int y=ed[i].v;
				if(lab[y]>0){
					int nt=(px+pot[y])>>1;
					if(lx!=lab[y]){
						if(nt==tim)return 1;
						aug=min(aug,nt);
					}
					else{
						if(bx==find(y))continue;
						if(nt==tim)contract(x,y),bx=find(x);
						else if(nt<=nh)push(lh,ln,nt,i);
					}
				}
				else if(lab[y]==FREE){
					int nt=px+1;
					if(nt==tim)grow(x,y,mt[y]);
					else if(nt<=nh)push(lh,ln,nt,i);
				}
			}
		}
		return 0;
	}
	bool advance(){
		int lim=min(nh+1,aug);
		for(++tim;tim<=lim;tim++){
			hs=hl;
			if(tim==lim)break;
			bool upd=0;
			for(int i=lh[tim];i>=0;i=ln[i]){
				auto e=ed[i]; int x=e.u,y=e.v;
				if(lab[y]>0){
					if(pot[x]+pot[y]!=(tim<<1) || find(x)==find(y))continue;
					if(lab[x]!=lab[y]) return aug=tim,0;
					contract(x,y); upd=1;
				}
				else if(lab[y]==FREE) grow(x,y,mt[y]),upd=1;
			}
			lh[tim]=-1;
			if(upd)return 0;
		}
		return tim>nh;
	}
	bool phase(){
		lab[0]=FREE;
		rep(i,1,n+1)
			if(!mt[i])q[qr++]=i,lab[i]=i;
			else lab[i]=FREE;
		for(;;){
			if(search())break;
			if(advance())return 0;
			if(tim==aug)break;
		}
		rep(i,1,n+1)
			if(lab[i]>0)pot[i]-=tim;
			else if(lab[i]<0)pot[i]=1+tim-pot[i];
		return 1;
	}
	void rematch(int v,int w){
		int x=mt[v]; mt[v]=w;
		if(mt[x]!=v)return;
		if(lk[v].v==find(lk[v].v))mt[x]=lk[v].u,rematch(mt[x],x);
		else{
			int a=lk[v].u,b=lk[v].v;
			rematch(a,b); rematch(b,a);
		}
	}
	bool dfs(int x,int bx){
		int px=pot[x],lx=lab[bx];
		for(int i=off[x];i<off[x+1];i++){
			int y=ed[i].v;
			if(px+pot[y])continue;
			int by=find(y),ly=lab[by];
			if(ly>0){
				if(lx>=ly)continue;
				int beg=sp;
				for(int v=by;v!=bx;v=find(lk[v].u)){
					int w=find(mt[v]);
					st[sp++]=w;
					lk[w]={x,y};
					dsu[v]=dsu[w]=bx;
				}
				while(sp>beg){
					int v=st[--sp];
					for(int u=bh[v];u>=0;u=bn[u]) if(dfs(u,bx))return sp=beg,1;
				}
			}
			else if(ly==FREE){
				lab[by]=INNER;
				int z=mt[by];
				if(!z){
					rematch(x,y); rematch(y,x);
					return 1;
				}
				int bz=find(z);
				lk[bz]={x,y}; lab[bz]=oid++;
				for(int v=bh[bz];v>=0;v=bn[v])if(dfs(v,bz))return 1;
			}
		}
		return 0;
	}
	int augment(){
		rep(i,1,n+1)dsu[i]=i;
		rep(i,0,hs)dsu[hist[i].u]=hist[i].v;
		rep(i,1,n+1)lab[i]=FREE,push(bh,bn,find(i),i);
		int ret=0;
		rep(i,1,n+1)if(!mt[i]){
			int b=dsu[i];
			if(lab[b]!=FREE)continue;
			lab[b]=oid++;
			for(int v=bh[b];v>=0;v=bn[v])if(dfs(v,b)){ret++;break;}
		}
		assert(ret); return ret;
	}
	void init(){
		q.resize(n); mt.assign(n+1,0);
		pot.assign(n+1,1); lab.assign(n+1,FREE);
		lk.assign(n+1,{0,0}); hist.resize(n);
		dsu.resize(n+1); lh.assign(nh+1,-1);
		ln.resize(sz(ed)); bh.assign(n+1,-1);
		bn.resize(n+1); st.resize(n); ql=qr=sp=0;
	}
	int solve(){
		init(); int ans=0;
		while(2*ans+1<n){
			reset();
			if(!phase())break;
			ans+=augment(); clear();
		}
		return ans;
	}
	vector<Edge> get(){
		vector<Edge> ans;
		rep(i,1,n+1)if(mt[i]>i)ans.pb({i-1,mt[i]-1});
		return ans;
	}
};

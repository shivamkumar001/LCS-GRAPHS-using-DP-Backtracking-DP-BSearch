#include <bits/stdc++.h>

using namespace std;

//nlogn
int fun(int idx, vector<int> &nums, int n, vector<int> &arr)
    {
        if(idx==n)
        {
            return arr.size();
        }
        if(idx==0)
        {
            arr.push_back(nums[idx]);
        }
        if(arr.back()<nums[idx])
        {
            arr.push_back(nums[idx]);
        }
        else
        {
            int lb=lower_bound(arr.begin(), arr.end(), nums[idx])-arr.begin();
            arr[lb]=nums[idx];
        }
        return max((int)arr.size(), fun(idx+1, nums, n, arr));
    }

int lengthOfLISdpbin(vector<int>& nums)
    {
        int n=nums.size();
        vector<int> arr;
        return fun(0, nums, n, arr);
    }

//n^2
int lengthOfLISdptab(vector<int>& a)
    {
        int ans=1;
        int n=(int)a.size();
        int dp[n];
        dp[0]=1;
        for(int i=1;i<n;i++)
        {
            dp[i]=1;
            for(int j=i-1;j>=0;j--)
            {
                if(a[j]<a[i])dp[i]=max(dp[i], 1+dp[j]);
            }
            ans=max(ans, dp[i]);
        }
        return ans;
    }

int fun2(vector<int>& a, int *dp, int n)
    {
        if(dp[n]!=-1)return dp[n];
        if(n==0)return 1;
        int maxi=0;
        for(int i=n-1;i>=0;i--)
        {
            if(a[i]<a[n])
            maxi=max(maxi, fun2(a, dp, i));
        }
        dp[n]=1+maxi;
        return dp[n];
    }

int lengthOfLISdpmem(vector<int>& a)
    {
        int n=(int)a.size();
        int dp[n];
        memset(dp, -1, sizeof(dp));
        return fun2(a, dp, n-1);
    }

//2^n

int LIS(vector<int>& a,int last,int now)
{
    if(now==a.size())return 0;
    int t = 0;
    if (a[now] > last)t = 1 + LIS(a, a[now], now + 1);
    int nt = LIS(a, last, now + 1);
    return max(t,nt);
}

int lengthOfLIS(vector<int>& a)
{
    return LIS(a,INT_MIN,0);
}

int main()
{
    vector<int> a;
    ifstream in;
    in.open("worst_case.txt");
    int temp;
    for(int i=0;i<10000;i++)
    {
        in>>temp;
        a.push_back(temp);
    }
    clock_t st, et;
    st=clock();
    cout<<lengthOfLISdpbin(a)<<endl;
    et=clock();
    cout<<fixed<<double(et-st)<<setprecision(5)<<"ms";
    return 0;
}

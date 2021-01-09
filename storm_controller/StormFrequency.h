 class StormFrequency{
    int high;
    int low;
    public:
      StormFrequency(int a,int b) {
          high = a;
          low = b;
      };
      int getHighFrequency () {return high;}
      int getLowFrequency () {return low;}
};

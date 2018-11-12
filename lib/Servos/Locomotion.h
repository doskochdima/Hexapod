class Locomotion {

public:
  Locomotion();

  void AttachLeg(int);
  void DetachLeg(int);

  void AttachAll();
  void DetachAll();

  void LegIK(float, float, float, float, float, float);

  void Idle();
  void Forward();

  void Test(int, int);
};

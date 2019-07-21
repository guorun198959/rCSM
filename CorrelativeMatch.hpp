#ifndef  _CORRELATIVE_MATCHES_H_
#define _CORRELATIVE_MATCHES_H_

#include<assert.h>
#include<vector>
#include<cstdlib>

#include<sensor_msgs/LaserScan.h>
#include<sensor_msgs/PointCloud.h>
#include<geometry_msgs/Transform.h>
#include<tf/transform_listener.h>
#include<tf/tf.h>

#include<eigen3/Eigen/Dense>

//#include<csm/csm.h>

#include<cmath>
#include <boost/graph/graph_concepts.hpp>
#include "predeal.hpp"


using namespace std;




namespace csm{

class likelihoodFiled{
public:

  likelihoodFiled(){}
  
  /**
   * \brief constructor function
   */
  explicit likelihoodFiled(const float& Windowsizes_,
		  const float  &sigma_ ,const float &map_resolution_ , const int &mapSizes_)
  {
    Windowsizes=Windowsizes_;
    mapSizes=mapSizes_;
    sigma=sigma_;
    map_resolution=map_resolution_;
    Eigen::MatrixXf map_(mapSizes_,mapSizes_);
    likehoodFiledMap=map_.setZero();
    map_origin<<int(mapSizes/2), int(mapSizes/2);
    guassK=generateGuassKernal(Windowsizes);
  }
  
  /*
   * TODO ���ƹ��캯��
   * 
   */
  
 void setParams(const float& Windowsizes_,
		  const float  &sigma_ ,const float &map_resolution_ , const int &mapSizes_)
  {
    Windowsizes=Windowsizes_;
    mapSizes=mapSizes_;
    sigma=sigma_;
    map_resolution=map_resolution_;
    Eigen::MatrixXf map_(mapSizes_,mapSizes_);
    likehoodFiledMap=map_.setZero();
    map_origin<<int(mapSizes/2), int(mapSizes/2);
    guassK=generateGuassKernal(Windowsizes);
  }
  
  /*
 float preScore(const Eigen::Vector2i& point)
 {
   float score_value;
   Eigen::Vector2f temp;
   temp=centriod-preDeal::gird2world(map_resolution,map_origin,point);   
  // cout<<temp<<endl;
   score_value=1/(2*3.141692f*pow(sigma,2))*exp(-temp.squaredNorm()/(2*pow(sigma,2)));
   return score_value;
}
*/

  /**
   * \brief generate a guassian kernel matrix ,which is used to smear the likelihoodFiled
   * \param[in] sizes the size of guassian kernel matrix 
   */
Eigen::MatrixXf generateGuassKernal(const int &sizes)
{
  if((sizes%2)!=1)
  {
    cout<<"sizes������һ������"<<endl;
    assert((sizes%2)==1);
  }
  Eigen::MatrixXf K;
  K.resize(sizes,sizes);
  //ֻ����1/8�����ݣ�����ȫ������
  for(int i=0;i<(sizes/2+1);i++)
  {
    for(int j=i;j<(sizes/2+1);j++)
    {
      Eigen::Vector2f temp;
      temp<<(sizes/2-i)*map_resolution,(sizes/2-j)*map_resolution;
      K(i,j)=log(1/((2*3.141692f)*pow(sigma,2))*exp(-temp.squaredNorm()/(2*pow(sigma,2))));
      //�����Ծ����з��������߸���
      K(i,sizes-j-1)=K(i,j);
      if(i!=j)
      {
      //��Ϊ�ǶԽǾ���,���ƶԽ�
      K(j,i)=K(i,j);
      K(j,sizes-i-1)=K(j,i);
      }
      if((sizes-i-1)!=i)
      {
      //�Ծ�����з���Ϊ�����߽��и���
      K.block(sizes-i-1,0,1,sizes)=K.block(i,0,1,sizes);
      }
    }
  }
  //�������������Ϊ����ϣ��������������
  return K/K.maxCoeff();
}
 
 /**
  * \brief ��ÿһ���㶼����һ����Ȼ������
  */
 bool  smear()
  {
    //cout<<"smear begin"<<endl;
    assert(point_cloud.points.size()>0); 
    for(int i=0;i<point_cloud.points.size();i++)
    {      
      //centriod<<point_cloud.points[i].x,point_cloud.points[i].y;
      centriod(0)=point_cloud.points[i].x;
      centriod(1)=point_cloud.points[i].y;
      Eigen::Vector2i centriod_gridType=preDeal::world2grid(map_resolution,map_origin,centriod);
      int size_girdType=Windowsizes;
      //cout<<"smear size:"<<size_girdType<<endl;
      //cout<<Windowsizes<<endl;
      assert(size_girdType>0);
      assert((centriod_gridType(0)-size_girdType/2)>0);
     int x=centriod_gridType(0)-size_girdType/2;
     int y=centriod_gridType(1)-size_girdType/2;
     
     //likehoodFiledMap.block(x,y,size_girdType,size_girdType)+=guassK;
     /*
     for(int i=centriod_gridType(0)-size_girdType/2,m=0;i<centriod_gridType(0)+size_girdType/2;i++,m++)
      {
	for(int j=centriod_gridType(1)-size_girdType/2,n=0;j<=centriod_gridType(1)+size_girdType/2;j++,n++)
	{
	    if(m>=Windowsizes||n>=Windowsizes)
	    {
	      cout<<"�������������߽�"<<endl;
	      assert(m<Windowsizes&&n<Windowsizes);
	    }
	   likehoodFiledMap(i,j)+=guassK(m,n);
	   if(likehoodFiledMap(i,j)>10*getMaxCoffsGuassianK())
	   {
	     likehoodFiledMap(i,j)=10*getMaxCoffsGuassianK();
	  }	  
	}
      }
      */
      
      
      
      for(int i=centriod_gridType(0)-size_girdType/2,m=0;i<centriod_gridType(0)+size_girdType/2;i++,m++)
      {
	for(int j=centriod_gridType(1)-size_girdType/2,n=0;j<=centriod_gridType(1)+size_girdType/2;j++,n++)
	{
	  if(guassK(m,n)>likehoodFiledMap(i,j))
	  {
	    if(m>=Windowsizes||n>=Windowsizes)
	    {
	      cout<<"�������������߽�"<<endl;
	      assert(m<Windowsizes&&n<Windowsizes);
	    }
	    likehoodFiledMap(i,j)=guassK(m,n);
	  }
	}
      }  
    }    
      return true;
  }
  
  
  
  
  /**
   * \brief ���õ��Ƹ��£����Ʊ������Ѿ�Ϊ��ͼ����ϵ��
   */
  Eigen::MatrixXf update(const sensor_msgs::PointCloud &mapPC)
  {
    assert(mapPC.points.size()>0);
    point_cloud=mapPC;
    if(likehoodFiledMap.rows()!=mapSizes)
    {
      likehoodFiledMap.resize(mapSizes,mapSizes);
    }
    likehoodFiledMap.setZero();
    if(smear())
   return likehoodFiledMap;
  }
  
  
  /**
   * ��ʼ��Ϊ�㣬���´���
   */
    Eigen::MatrixXf create(const sensor_msgs::PointCloud &mapPC)
  {
    assert(mapPC.points.size()>0);
    point_cloud=mapPC;
    if(likehoodFiledMap.rows()!=mapSizes)
    {
      likehoodFiledMap.resize(mapSizes,mapSizes);
    }
    likehoodFiledMap.setZero();
    if(smear())
   return likehoodFiledMap;
  }
  
  Eigen::MatrixXf getlikelihoodField()
  {
    
    if(smear())
    return likehoodFiledMap;
  }
  
  float getMapResolution() const
  {
    return map_resolution;
  }
  
  Eigen::Vector2i getMapOrigin() const
  {
    return map_origin;
  }
  
  inline float getMaxCoffsGuassianK() const
  {
    return guassK.maxCoeff();
  }
  
private:

   float map_resolution;
   //���������
  Eigen::Vector2f centriod;
  //���µ������С��Windowsizes * Windowsizes������Ϊդ���������������Ϊ��������ʾ����
  int Windowsizes;
  //�����������
  float sigma;
  //��ŵ��ƣ�����������Ȼ��
  sensor_msgs::PointCloud point_cloud;
  //��Ȼ��
  Eigen::MatrixXf likehoodFiledMap;
  //������Ȼ���Ĵ�С
  int mapSizes;
  //��ͼ����ϵԭ���ھ�������ϵ�µ�λ�ã�һ������Ϊ�ھ��������
  Eigen::Vector2i map_origin;
  //��Ÿ�˹�ˣ����ڸ�����Ȼ��
  Eigen::MatrixXf guassK;
};



class CorrelativeMatch{
  
public:
	enum lookMethod
	{
		bruteForce,
		slice2D,
		MutiResolution
	};
  CorrelativeMatch()  {
    searchMethod="brute force";
    favor_threshold=1.0;
  }
  
  CorrelativeMatch( Eigen::Vector3f poseWindowSizes_)
  {
    poseWindowSizes=poseWindowSizes_;
  }
  
  /*
   * ���ƹ��캯��
   * TODO
   * 
   */
  void setSearchWindowSizes(Eigen::Vector3f poseWindowSizes_)
  {
    poseWindowSizes=poseWindowSizes_;
  }
  
  void setSearchStepLength(const float &x_resolution_, const float &y_resolution_,const float &orientation_resolution_)
  {
    assert(x_resolution_>0&&y_resolution_>0&&orientation_resolution_>0);
    x_resolution=x_resolution_;
    y_resolution=y_resolution_;
    orientation_resolution=orientation_resolution_;
  }
  
  void setSearchMethod(const string &searchMethod_)
  {
    searchMethod=searchMethod_;
  }
  
  void setFavorThreshod(const float &percent)
  {
    favor_threshold=percent;
  }
 
 
 /**
  * ʹ�ñ������ҵķ���
  */  
  Eigen::Vector3f BruteForceLookup() const
  {
    float bound=pc_base.points.size()*favor_threshold*llf.getMaxCoffsGuassianK();
    float score_Max=score(poseWindowCentriod);
    if(score_Max>bound)
    {
      return poseWindowCentriod;
    }
    Eigen::Vector3f beset_state=poseWindowCentriod;
    for(int i=0;i<floor(poseWindowSizes(0)/x_resolution);i++) 
    {
       float pose_x=poseWindowCentriod(0)-poseWindowSizes(0)/2+i*x_resolution;
      for(int j=0;j<floor(poseWindowSizes(1)/y_resolution);j++)
      {
	  float pose_y=poseWindowCentriod(1)-poseWindowSizes(1)/2+j*y_resolution;
	for(int k=0;k<floor(poseWindowSizes(2)/orientation_resolution);k++)
	{	
	  float theta=poseWindowCentriod(2)-poseWindowSizes(2)/2+k*orientation_resolution;
	  /*
	  tf::Transform tf_;
	  tf::Quaternion q(0,0,sin(theta/2),cos(theta/2));
	  tf::Vector3 Origin(pose_x,pose_y,0);	  
	  tf_.setRotation(q);
	  tf_.setOrigin(Origin);
	  */
	  Eigen:: Vector3f state(pose_x,pose_y,theta);
	  float scoreValue=score(state);
	  if(scoreValue>score_Max&&scoreValue<=bound)
	  {
	    cout<<"����һ�����õ�pose"<<endl;
	    score_Max=scoreValue;
	    beset_state=state;
	  }
	  else if (scoreValue>bound)
	  {
	    return state;
	  }
	}
      }
    }
    return beset_state;
    //return poseWindowCentriod;
  }
  
  
  
  //��Ƭ��Ŀ����Ϊ�˽�Լ����ʱ�䣬����������ת��һ���ȼ�����ת����ô�ڲ��Ϳ����ټ���N*N����ת��  
   Eigen::Vector3f SilceLookup() const
  {
    float bound=pc_base.points.size()*favor_threshold*llf.getMaxCoffsGuassianK();
    float score_Max=score(poseWindowCentriod);
    if(score_Max>=bound)
    {
      return poseWindowCentriod;
    }    
    int theta_sizes=floor(poseWindowSizes(2)/orientation_resolution);
    int x_sizes=floor(poseWindowSizes(0)/x_resolution);
    int y_sizes=floor(poseWindowSizes(1)/y_resolution);        
    Eigen::Vector3f best_state=poseWindowCentriod;    
    for(int i=0;i<theta_sizes;i++) 
    {
       sensor_msgs::PointCloud RotatededPC;
      float theta=poseWindowCentriod(2)-poseWindowSizes(2)/2+i*orientation_resolution;
      Eigen::Quaternion<float> q(cos(theta)/2,0,0,sin(theta)/2);
       for(int i_=0;i_<pc_base.points.size();i_++)
	{	
	    Eigen::Vector3f tempoint;
	    tempoint<<pc_base.points[i_].x, pc_base.points[i_].y,0;
	    tempoint=q.toRotationMatrix()*tempoint;
	     geometry_msgs::Point32 tempointx;
	  tempointx.x=tempoint(0);tempointx.y=tempoint(1);tempointx.z=0;
	  RotatededPC.points.push_back(tempointx);
	} 
      
      for(int j=0;j<x_sizes;j++)
      {
	float pose_x=poseWindowCentriod(0)-poseWindowSizes(0)/2+j*x_resolution;
	  
	for(int k=0;k<y_sizes;k++)
	{	  
	  float pose_y=poseWindowCentriod(1)-poseWindowSizes(1)/2+k*y_resolution;
	  float sum=1;
	 for(int ii=0;ii<RotatededPC.points.size();ii++)
	{   
	  Eigen::Vector2i temIndex;
	  Eigen::Vector2f point2d;
	  point2d(0)=RotatededPC.points[ii].x+pose_x;
	  point2d(1)=RotatededPC.points[ii].y+pose_y;	  
	   temIndex=preDeal::world2grid(llf.getMapResolution(),llf.getMapOrigin(),point2d);
	  if(temIndex(0)>=0&&temIndex(0)<llfmap.rows() &&temIndex(1)>=0&&temIndex(1)<llfmap.cols())
	  sum+=llfmap(temIndex(0),temIndex(1));	    
	} 
	  Eigen:: Vector3f state(pose_x,pose_y,theta);
	  if(sum>score_Max&&sum<=bound)
	  {
	    cout<<"����һ�����õ�pose"<<endl;
	    score_Max=sum;
	    best_state=state;
	  }
	  else if (sum>bound)
	  {
	    return state;
	  }
	}
      }
    }
    return best_state;
  }
  
  
  
  
  //�ڵ��Ƴ��õ���д��pc
  //��Ҫ��֤��ros�����е�stampTransform�������˼���ǵõ�ת����ϵ���ǰ�child_frame_id���ݴ���frame_id�£���������transformʱ��Ҳ�Ǳ��밴���������
  
  /**
   * \brief ��ת����ϵ���д�֣���ֵ�������еļ���hits�ĵ㱻ת����map����ϵ�£�����Ȼ���еķ����ĳ˻���������͵�Ч��Ҫ��
   * \param[in] tf_ laser��map��ת����ϵ
   */
  float score(const tf::Transform &tf_) const
  {
    float tf_score=1;        
   for(int i=0;i<pc_base.points.size();i++)
   {
     Eigen::Vector2i temIndex;
     Eigen::Vector3f tempoint;
     Eigen::Vector2f point2d;
     tempoint<<pc_base.points[i].x, pc_base.points[i].y,0;
     Eigen::Quaternion<float> q(tf_.getRotation().w(),tf_.getRotation().x(),tf_.getRotation().y(),tf_.getRotation().z());
     Eigen::Vector3f trans(tf_.getOrigin().x(),tf_.getOrigin().y(),tf_.getOrigin().z());
     tempoint=q.toRotationMatrix()*tempoint+trans;
     point2d<<tempoint(0),tempoint(1);
     temIndex=preDeal::world2grid(llf.getMapResolution(),llf.getMapOrigin(),point2d);
     if(temIndex(0)>=0&&temIndex(0)<llfmap.rows() &&temIndex(1)>=0&&temIndex(1)<llfmap.cols())
     tf_score+=llfmap(temIndex(0),temIndex(1));     
  }    
  }
  
  float score(const Eigen::Vector3f &tf_) const
  {
    float tf_score=0;        
   for(int i=0;i<pc_base.points.size();i++)
   {
     assert(!pc_base.points.empty());
     Eigen::Vector2i temIndex;
     Eigen::Vector3f tempoint;
     Eigen::Vector2f point2d;
     tempoint<<pc_base.points[i].x, pc_base.points[i].y,0;
     Eigen::Quaternion<float> q(cos(tf_(2)/2),0,0,sin(tf_(2)/2));
     Eigen::Vector3f trans(tf_(0),tf_(1),0);
     tempoint=q.toRotationMatrix()*tempoint+trans;
     point2d<<tempoint(0),tempoint(1);
     temIndex=preDeal::world2grid(llf.getMapResolution(),llf.getMapOrigin(),point2d);
     if(temIndex(0)>=0&&temIndex(0)<llfmap.rows() &&temIndex(1)>=0&&temIndex(1)<llfmap.cols())
     tf_score+=llfmap(temIndex(0),temIndex(1));     
  }
  return tf_score;
  }  
  
  /**
   * \brief update likehood field
   * \param[in] llf_ ���ڼ������Ȼ�� 
   */
  void updataikehoodField(const likelihoodFiled &llf_)
  {
    llf=llf_;
    llfmap=llf.getlikelihoodField();  
  }
  
  
  bool llfIsEmpty()
  {
    if(llfmap.cols()==0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
  /*���������
  Eigen::Vector3f getCorrelativePose(const sensor_msgs::LaserScan & scan_,const Eigen::Vector3f &poseWindowCentriod_)
  {
    preDeal::scan2pc(scan_,currentPCinLaserFrame);
    poseWindowCentriod=poseWindowCentriod_;
    relativePose=lookup();
    return relativePose;
  }
  */
  
    Eigen::Vector3f getCorrelativePose(const sensor_msgs::PointCloud & pc_base_,const Eigen::Vector3f &poseWindowCentriod_)
  {
    pc_base=pc_base_;
    poseWindowCentriod=poseWindowCentriod_;
   if(searchMethod=="brute force" )
   {
     relativePose=BruteForceLookup();
  }
  else if(searchMethod=="slice")
  {
     relativePose=SilceLookup();
  }
  else
  {
    cout<<"û����Ӧ��������������ƥ�䣬���������� "<<endl;
    exit(0);
  }
    // relativePose=lookup();
   
    return relativePose;
  }
  
private:
  //����ʱx�ķֱ���
  float x_resolution;
  //����ʱ�ķֱ���
  float y_resolution;
  //����ʱ�Ƕȵķֱ���
  float orientation_resolution;
  //����λ�ã������ľ���
  Eigen::Vector3f poseWindowCentriod;
  //���ĳߴ磬��λ���ף���Ϊ�����������Խ����Ӧ�����õ�Խ��
  Eigen::Vector3f poseWindowSizes;
  //Ŀǰ������Եģ��õ���ֱ�Ӿ���λ��
  Eigen::Vector3f relativePose;
  //��base����ϵ�µĵ�������
  sensor_msgs::PointCloud pc_base;
  //��Ȼ��
 likelihoodFiled llf;
 //�����Ȼ���ĵ�ͼ��Ϣ
 Eigen::MatrixXf llfmap;
 //����λ�˵ķ���
 string searchMethod;
 //��ֵ
 float favor_threshold;
};


class RealTimeCorrelativeScanMatch: public CorrelativeMatch
{
public:
RealTimeCorrelativeScanMatch(){}

private:
Eigen::MatrixXf generateMultiResoltionMap()
{}
  
};


}


#endif

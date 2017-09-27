# qtsimplescada
This is constructor for simple Scada UI. In order of any questions please conatact ask@indeema.com

<a href="http://www.indeema.com">
  <p align="center">
  <img src="http://indeema.com/images/logoIn.png" alt="Indeema Logo"/>
</p>
</a>

<br>
We created this simple qt Scada sdk to easily create UIs that shows some objects with their statuses. 
You can add any number of objects with any marker or background image for each state.
<br>

Preview
<br>
<br>
  <img src="/resources/SampleScada.png" alt="Floating menu" width="800" height="410" />
<br>
In MainWindow class we have realisation on VSimpleScada usage. With window in edit mode and config panel at the left side.
<br>
As a sample first two objects are created as dynamic with visible marker and the third object is background object on which you cah locate your markers
<br>
VObject class is used to display marker or background view. It can be managed by updating setInfo, using container VObjectInfo.
<br>
In resources path you can find sample.irp file. Open it with QSampleScada app to see sample

# QSimpleScadaSample
This is constructor for simple Scada UI. In order of any questions please conatact ask@indeema.com

<a href="http://www.indeema.com">
  <p align="center">
  <img src="http://indeema.com/images/logoIn.png" alt="Indeema Logo"/>
</p>
</a>

To test this sample install qpm (https://www.qpm.io) and run in project root qpm install. Or download QSimpleScada (https://github.com/IndeemaSoftware/QSimpleScada)

<br>
We created these simples that are using qt Scada sdk to easily create UIs that shows some objects with their statuses. 
You can add any number of objects with any marker or background image for each state.

Builder - simple dashboard builder
Weather - weather checking application that shows data od predeveloped dashboard
<br>

Preview
<br>
<br>
<img src="https://github.com/IndeemaSoftware/QSimpleScada/blob/Assets/qsimplescada.gif" />

<h1 align="center"><img src="https://github.com/IndeemaSoftware/EEIoT/blob/Assets/weather.png"/><br> Weather application</h1>
<br>
In MainWindow class we have realisation on QSimpleScada usage. With window in edit mode and config panel at the left side.
<br>
As a sample first two objects are created as dynamic with visible marker and the third object is background object on which you cah locate your markers
<br>
QScadaObject class is used to display marker or background view. It can be managed by updating setInfo, using container QScadaObjectInfo.
<br>
In resources path you can find sample.irp file. Open it with QSampleScada app to see sample

To know more about us and our [IoT expertise](https://indeema.com/services/iot), visit our website http://indeema.com

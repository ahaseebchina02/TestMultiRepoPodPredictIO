
Pod::Spec.new do |s|
  s.name             = 'TestMultiRepoPodPredictIO'
  s.version          = '0.1.0'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.homepage         = 'https://github.com/ahaseebchina02/TestMultiRepoPodPredictIO.git'
  s.summary          = 'The parking detection API (patent pending) allows you to retrieve real-time updates on the parking status of a user.'
  s.author           = { 'ahaseebchina02' => 'ahaseebchina02@gmail.com' }

  s.source           = { :git => 'https://github.com/ahaseebchina02/TestMultiRepoPodPredictIO.git', :tag => s.version.to_s }

  s.platform = :ios
  s.ios.deployment_target = '7.0'
  s.requires_arc = true

  s.source_files = 'TestMultiRepoPodPredictIO/Classes/**/*'
 s.vendored_library = 'TestMultiRepoPodPredictIO/libPredictIO.a'
  
  s.frameworks = 'UIKit', 'CoreMotion', 'CoreLocation', 'CoreTelephony', 'AdSupport', 'AVFoundation', 'CoreBluetooth', 'SystemConfiguration', 'ExternalAccessory'

#2
  s.description      = "You may use the parking updates to trigger events or notifications specific to your use case. The parking detection service stack leverages all available phone sensors. Sensor usage is extremely battery optimized. Incremental battery consumption does not exceed 10% in typical cases. Also we strongly suggest you ensure inclusion of LBS in your T&C and Privacy Policies. By using this API you explicitly agree to our license agreement, terms and conditions and privacy policy. If you are unsure about any item, please contact us at support@parktag.mobi."
  
end


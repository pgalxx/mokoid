/* mokoid/hardware/ILedService.aidl
**
** Copyright 2009 The Mokoid Open Source Project
** Copyright 2009 Moko365 Inc
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

package mokoid.hardware;

/*
 * ILedService.Stub 
*/
interface ILedService
{
    boolean setOn(int led);
    boolean setOff(int led);
}
//aidl是一个工具，从android sdk的开发里面可找到该工具的说明；aidl本质是一个代码产生器，它的语法是java代码，第三 它帮我们产生代码。
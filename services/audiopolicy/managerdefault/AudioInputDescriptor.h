/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

namespace android {

// descriptor for audio inputs. Used to maintain current configuration of each opened audio input
// and keep track of the usage of this input.
class AudioInputDescriptor: public AudioPortConfig
{
public:
    AudioInputDescriptor(const sp<IOProfile>& profile);

    status_t    dump(int fd);

    audio_port_handle_t           mId;
    audio_io_handle_t             mIoHandle;       // input handle
    audio_devices_t               mDevice;         // current device this input is routed to
    AudioMix                      *mPolicyMix;     // non NULL when used by a dynamic policy
    audio_patch_handle_t          mPatchHandle;
    uint32_t                      mRefCount;       // number of AudioRecord clients using
    // this input
    uint32_t                      mOpenRefCount;
    audio_source_t                mInputSource;    // input source selected by application
    //(mediarecorder.h)
    const sp<IOProfile>           mProfile;        // I/O profile this output derives from
    SortedVector<audio_session_t> mSessions;       // audio sessions attached to this input
    bool                          mIsSoundTrigger; // used by a soundtrigger capture

    virtual void toAudioPortConfig(struct audio_port_config *dstConfig,
            const struct audio_port_config *srcConfig = NULL) const;
    virtual sp<AudioPort> getAudioPort() const { return mProfile; }
    void toAudioPort(struct audio_port *port) const;
};

}; // namespace android

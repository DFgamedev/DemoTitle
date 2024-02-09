#include "ChatGPTAPIWrapper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/ConfigCacheIni.h"


UChatGPTAPIWrapper::UChatGPTAPIWrapper()
{
}

void UChatGPTAPIWrapper::SetOpenAIAPIKey(const FString& APIKey)
{
	OpenAIAPIKey = APIKey; 
}

FString UChatGPTAPIWrapper::GetOpenAIAPIKey()
{
	if(!OpenAIAPIKey.IsEmpty())
	{
		return OpenAIAPIKey;
	}

	FString APIKey;
	if (GConfig->GetString(TEXT("OpenAI"), TEXT("APIKey"), APIKey, GEngineIni))
	{
		return APIKey;
	}
	return TEXT("");
}

void UChatGPTAPIWrapper::SendRequest(const FString& Prompt, const FOnSuccessDelegate& OnSuccess, const FOnErrorDelegate& OnError)
{
	FString APIKey = GetOpenAIAPIKey();
	if(!APIKey.IsEmpty())
	{
		FHttpModule* Http = &FHttpModule::Get();
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
		Request->OnProcessRequestComplete().BindUObject(this, &UChatGPTAPIWrapper::OnResponseReceived, OnSuccess, OnError);
		Request->SetURL("https://api.openai.com/v1/engines/text-davinci-003/completions");
		// Request ->SetURL (https://api.openai.com/v1/engines/text-davinci-003/completions)
		Request->SetVerb("POST");
		Request->SetHeader("Content-Type", "application/json");
		Request->SetHeader("Authorization", FString::Printf(TEXT("Bearer %s"), *APIKey));

		// Customize the request payload as needed
		TSharedPtr<FJsonObject> JsonRequestObject = MakeShareable(new FJsonObject);
		JsonRequestObject-> SetStringField("prompt", Prompt);
		JsonRequestObject-> SetNumberField("max_tokens", MaxTokens);

		// Customize the request payload as needed
		JsonRequestObject-> SetNumberField("temperature", Temperature);
		JsonRequestObject-> SetNumberField("top_p", TopP);

		FString JsonPayload;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonPayload);
		FJsonSerializer::Serialize(JsonRequestObject.ToSharedRef(), JsonWriter);

		Request->SetContentAsString(JsonPayload);
		Request->ProcessRequest();
	}
	else
	{
		OnError.Execute(-1, TEXT("OpenAI API key not found or invalid"));
	}
}

void UChatGPTAPIWrapper::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnSuccessDelegate OnSuccess, FOnErrorDelegate OnError)
{
	if (bWasSuccessful && Response.IsValid())
	{
		if (Response->GetResponseCode() == 200)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				TArray<TSharedPtr<FJsonValue>> Choices = JsonObject->GetArrayField("choices");
				if (Choices.Num() > 0)
				{
					TSharedPtr<FJsonObject> ChoiceObject = Choices[0]->AsObject();
					FString GeneratedText = ChoiceObject->GetStringField("text");

					OnSuccess.Execute(GeneratedText);
				}
				else
				{
					OnError.Execute(Response->GetResponseCode(), TEXT("No choices were returned by the API"));
				}
			}
			else
			{
				OnError.Execute(Response->GetResponseCode(), TEXT("Failed to parse the JSON response"));
			}
		}
		else
		{
			OnError.Execute(Response->GetResponseCode(), FString::Printf(TEXT("API returned an error. Response code: %d"), Response->GetResponseCode()));
		}
	}
	else
	{
		OnError.Execute(-1, TEXT("Failed to Connect to the OpenAI API"));
	}
}





